#ifndef _LIB_IMPORT_GAME_IMAC_LSM
#define _LIB_IMPORT_GAME_IMAC_LSM
#pragma once

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/Library.hpp>
#include <glimac/Render.hpp>
#include <algorithm>
#include <functional>


namespace sausageRunner {
	

	/*! \class Personnage
	   * \brief
	   *	Class stock all information about te main character
	   *  	
	   */
	class Personnage{
		private:
			int _id; //!< id of the model in the vector _persos of the game lib
			int _x_state = 0; // -1 : left, 0 : middle, 1 : right //!< State in X axis of the character in the game
			int _y_state = 0; // 0 : normal, 1 : jump, -1 : down //!< State in Y axis of the main character in the game

			int _last_x_state = 0; //!< Stock the last x state

			int _last_x = 0; //!< Stock the global time of the last state changement ion the X axis
			int _last_y = 0; //!< Stock the global time of the last state changement ion the X axis
			int _points = 0;

			int nbFrameForSmoothTranslation = 10; //!< Number of frames to visually go from the current X state to the asked X state
			int jumpTime = 50; //!< Number of frames of a jump

	 	public:

	 		Personnage(int id):_id(id){}
	 		void setId(int id){ _id = id;}
	 		int id()const{return _id;}
			
			/*!
			 * \brief To set the Y state of the character
			 */
			void move_jump_bend(int state, int t){
				int deltaT = t-_last_y;
				if(deltaT > jumpTime)
				{
					_y_state = state;
					_last_y = t;
				}
			}
		
			/*!
			 * \brief To set the X state of the character
			 */
			void move_left_right(int state, int t){
				_last_x_state = _x_state;
				_x_state = state;
				_last_x = t;}
			int get_x_state(){
				return _x_state;}
			int get_y_state(){
				return _y_state;}
			void set_last_x(int i){
				_last_x = i;}
			void set_last_y(int i){
				_last_y = i;}
			
			/*!
			 * \brief To get the visual X position, it's an easing transition between the last state and the current state
			 */
			float getRealX(int t)
			{
				int deltaT = t - _last_x;
				if(deltaT < nbFrameForSmoothTranslation) return (_x_state - _last_x_state)*sin(deltaT/float(nbFrameForSmoothTranslation) * M_PI/2) +_last_x_state;
				return _x_state;
			}
			/*!
			 * \brief To get the visual Y position, it's an easing transition for jump or bend and turn to the initial state at the end
			 */
			float getRealY(int t)
			{
				int deltaT = t-_last_y;
				if(deltaT < jumpTime)
				{
					if(_y_state == 1) return _y_state*sin(deltaT/float(jumpTime) * M_PI);
				}
				else
					_y_state = 0;
				return _y_state;
			}
			
			std::vector<int> getBbox();
			bool collide(LibElem *obs){
				std::vector<int> persoBbox = getBbox();
				std::vector<int> obsBbox = obs->getBbox();
				int i = 0;
				while(i < obsBbox.size() && i < persoBbox.size()){
					if(persoBbox[i] + obsBbox[i] == 2) return true;
					i++;
				}
				return false;
			}
	};

	/*! \class World
	   * \brief
	   *	Group the gestion of all the entities of the game world
	   *  
	   */
	class World
	{
		private:
			float _t = 0; //!< advance of the world
			float _speed = 0.15; //!< Speed of the world
			unsigned int lastTile = -1; //!< Save the last collided tile
			std::vector<Tile> _tiles; //!< Vector of all tiles
			bool _randomized = false; // True : the world will be generated, False : the world will be loaded from a file

			glm::mat4 _globalPosition; //!< Save the global position of the world (because we choose to move the world and not the character
			glm::mat4 _globalRotation; //!< Save the global rotation of the world, to update light position
			glm::mat4 _firstTileMatrix;

			Personnage *_perso;
			Library *_modelLib;
			Render *_render;

			SimpleAxeCam *_aroundCam; //!< Camera to see around the character
			SimpleAxeCam *_eyesCam; //!< First Person camera

			unsigned short int _activeCam = 0; //!< Save the active Cam
		    bool rightClickDown = false; //!< Keep the current state of the right click of the mouse to update cam
		    bool edit_mode = true; //!< Used to lock or unlock the Camera edition
		    int lastX = 0, lastY = 0; //!< Save the last mouse position to calculate the motion of the camera
		    int _currentBonus = -1; //!< The current bonus
		    int _lastTimeBonus = 0; //!< The global time of the last bonus taken

		    int _lastRotation = 0; //!< The last rotation of the character, to smooth the camera movement
		    int _lastTimeRotation = 0;	//!< The global time of the last rotation
		    int _timeToSmoothCamRotation = 30; //!< Duration of camera smoothing for the rotation
		    int _timeStartGame = 0; //!< The global time of the beginning of the last game

		    int _bonusInfluenceTime = 300; //!< The time of the influence of the current bonus

		    int _nCoin = 0; //!< Number of coin collected

		    int _beginningAnimDuration = 100; //!< Duration of the beginning animation
		    float _zoomBeginningAnimation = 10; //!< Value of the camera zoom during the beginning animation

			void loadFile(std::string level); // Fill the vector _tiles with the file;

		public:
			World(std::string file = ""){
				if(file == "") _randomized = true;
				else loadFile(file);
				_aroundCam = new TrackballCamera(5.0f + _zoomBeginningAnimation,25.0f,0.0f);
	     		_eyesCam = new EyesCam(30.0f,0.0f);
	     		_eyesCam->setPosition(glm::vec3(0.0f,-1.4f,0.2f));
	     		_perso = new Personnage(0);
			}
			
			/*!
			 * \brief Return a pointer of the current camera
			 */
			SimpleAxeCam* cam(){
				if(_activeCam == 0) return _aroundCam;
				return _eyesCam;
			}
			
			/*!
			 * \brief Change the current camera
			 */
			void changeCam(){
				if(_activeCam == 0) _activeCam = 1;
				else _activeCam = 0;
			}
			
			/*!
			 * \brief Add a tile at th end
			 */
			void addTile(Tile* t); // add tile at the endcqjkcdhsqhs hdgzusgz  zsgyzgs nina la meilleure de toutev
			
			/*!
			 * \brief Draw all the elements of the World class
			 */
			int draw(int global_time);
			
			/*!
			 * \brief Calculate the collision between the character and the current tile
			 */
			int collision(int global_time, int currentTile);
			
			/*!
			 * \brief Set a library of model
			 */
			void setLibrary(Library *lib){
				_modelLib = lib;
			}
			
			/*!
			 * \brief Set a render manager
			 */
			void setRender(Render *r){
				_render = r;
			}
			
			/*!
			 * \brief Check if the bonus advantages are done or not
			 */
			void checkBonus(int global_time);
			
			/*!
			 * \brief Set the current bonus if there is no current bonus anymore
			 */
			bool setBonus(int b, int global_time);

			
			/*!
			 * \brief Initialize the world
			 */
			void init(int global_time)
			{
				_timeStartGame = global_time;
				std::function<void(Tile t)> resetTile = [](Tile t){
					t.reset();
				};
				for_each(_tiles.begin(), _tiles.end(),resetTile);
				resume();
				_aroundCam->reset(5.0f + _zoomBeginningAnimation,35.0f,0.0f);
				_globalPosition = glm::mat4();
				_globalRotation = glm::mat4();
				_t = 0.0;
				lastTile = -1;
				_activeCam = 0;
			}
			
			/*!
			 * \brief Resume the game
			 */
			void resume()
			{
				_render->use();
				glEnable(GL_DEPTH_TEST);
			}
			
			/*!
			 * \brief Close the game
			 */
			void close()
			{
				glDisable(GL_DEPTH_TEST);
			}
			
			/*!
			 * \brief Add coins
			 */
			void addCoin(int n)
			{
				_nCoin += n;
			}
			
			/*!
			 * \brief Return the number of coins collected
			 */
			int getCoin()
			{
				return _nCoin;
			}
			
			/*!
			 * \brief Return the last score
			 */
			int getScore()
			{
				return int(_t) * 100;
			}
			
			/*!
			 * \brief Return a pointer of the character
			 */
			Personnage* perso(){return _perso;}
			
			/*!
			 * \brief Get the mouse motion and change the cam thanks that
			 */
			void mouseMotion(int x,int y){
			    if(rightClickDown && edit_mode){
				cam()->rotateLeft(y-lastY);
				cam()->rotateTop(x-lastX);
				lastX = x;
				lastY = y;
			    }
			}
			
			/*!
			 * \brief Get the mouse button down event and process it
			 */
			void mouseButtonDown(Uint8 btn){
			    if(btn == SDL_BUTTON_RIGHT) {
				rightClickDown = true;
				SDL_GetMouseState(&lastX, &lastY);
			    }
			    else if(btn == SDL_BUTTON_WHEELUP && edit_mode){
				cam()->moveFront(0.3);
			    }
			    else if(btn == SDL_BUTTON_WHEELDOWN && edit_mode){
				cam()->moveFront(-0.3);
			    }
			}
			
			/*!
			 * \brief Get the mouse button up event and process it
			 */
			void mouseButtonUp(Uint8 btn){
			    if(btn == SDL_BUTTON_RIGHT) {
				rightClickDown = false;
			    }
			}
			
			/*!
			 * \brief Get the key button down event and process it
			 */
			void keyDown(Uint8 key, int t){
			    switch(key) {
				case SDLK_z: // z to jump
				     _perso->move_jump_bend(1, t);
				    break;
				case SDLK_s: //s to bend
				    _perso->move_jump_bend(-1, t);
				    break;
				case SDLK_q: //q to go left
				    _perso->move_left_right(-1, t);
				    break;
				case SDLK_d: //d to go right
				    _perso->move_left_right(1, t);
				    break;
				case SDLK_l: //l camera edit mode
				    if(edit_mode)
					edit_mode = false;
				    else
					edit_mode = true;
				    break;
				case SDLK_c: //c to change camera
				    changeCam();
			    }
			}
			
			/*!
			 * \brief Get the key up down event and process it
			 */
			void keyUp(Uint8 key, int t){
			    switch(key) {
					case SDLK_z:
					    _perso->move_jump_bend(0, t);
					    break;
					case SDLK_s:
					    _perso->move_jump_bend(0, t);
					    break;
					case SDLK_q:
					    _perso->move_left_right(0, t);
					    break;
					case SDLK_d:
					    _perso->move_left_right(0, t);
					    break;
			    }
			}
			
			/*!
			 * \brief Save the last rotation of the world (to smooth the camera)
			 */
			void setLastRotation(int way, int global_time)
			{
				_lastRotation = way;
				_lastTimeRotation = global_time;
			}
			
			/*!
			 * \brief Return an angle to rotation the view matrix to smooth the camera motion at the world rotations
			 */
			float getSmoothCamAngle(int global_time)
			{
				int detlaT = global_time - _lastTimeRotation;
				if(detlaT > _timeToSmoothCamRotation) return 0.0;
				return -_lastRotation * (M_PI/2.0) * (1.0 - float(detlaT)/float(_timeToSmoothCamRotation));
			}
	};
}

#endif

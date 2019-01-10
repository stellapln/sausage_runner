#ifndef _LIB_IMPORT_GAME_IMAC_LSM
#define _LIB_IMPORT_GAME_IMAC_LSM
#pragma once

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/Except.hpp>
#include <glimac/Library.hpp>
#include <glimac/Render.hpp>
#include <algorithm>
#include <functional>

#define NB_FRAME_FOR_SMOOTH_TRANSLATION 10
#define NB_FRAME_FOR_JUMP 50
#define DETECT_COLLISION_VALUE 2
#define INITIAL_GAME_SPEED 0.15
#define NB_FRAME_FOR_SMOOTH_CAM_ROTATION 30
#define NB_FRAME_FOR_BONUS_INFLUENCE 300
#define NB_FRAME_FOR_BEGINNING_ANIMATION 100
#define ZOOM_VALUE_FOR_BEGINNING_ANIMATION 10
#define DISTANCE_CAMERA_CHARACTER 5.0f
#define ANGLE_OF_CAMERA 35.0f
#define MULT_VALUE_FOR_SCORE 100
#define MOVE_FRONT_VALUE_ON_MOUSE_WHEEL 0.3
#define NB_FRAME_OF_END_ANIMATION 20
#define PERSO_ANGLE_END_ANIMATION -80

namespace sausageRunner {
	

	/*! \class Personnage
	   * \brief
	   *	Class stock all information about te main character
	   *  	
	   */
	class Personnage{
		private:
			int _id; /*!< id of the model in the vector _persos of the game lib*/
			int _x_state = 0; // -1 : left, 0 : middle, 1 : right /*!< State in X axis of the character in the game*/
			int _y_state = 0; // 0 : normal, 1 : jump, -1 : down /*!< State in Y axis of the main character in the game*/

			int _last_x_state = 0; /*!< Stock the last x state*/

			int _last_x = 0; /*!< Stock the global time of the last state changement ion the X axis*/
			int _last_y = 0; /*!< Stock the global time of the last state changement ion the X axis*/
			int _points = 0;

			int nbFrameForSmoothTranslation = NB_FRAME_FOR_SMOOTH_TRANSLATION; /*!< Number of frames to visually go from the current X state to the asked X state*/
			int jumpTime = NB_FRAME_FOR_JUMP; /*!< Number of frames of a jump*/

	 	public:

	 		Personnage(const int id):_id(id){}
	 		void setId(const int id){ _id = id;}
	 		int id()const{return _id;}
			
			/*!
			 * \brief To set the Y state of the character
			 */
			void move_jump_bend(const int state, const int t){
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
			void move_left_right(const int state, const int t){
				_last_x_state = _x_state;
				_x_state = state;
				_last_x = t;}
			int get_x_state(){
				return _x_state;}
			int get_y_state(){
				return _y_state;}
			void set_last_x(const int i){
				_last_x = i;}
			void set_last_y(const int i){
				_last_y = i;}
			
			/*!
			 * \brief To get the visual X position, it's an easing transition between the last state and the current state
			 */
			float getRealX(const int t)
			{
				int deltaT = t - _last_x;
				if(deltaT < nbFrameForSmoothTranslation) return (_x_state - _last_x_state)*sin(deltaT/float(nbFrameForSmoothTranslation) * M_PI/2) +_last_x_state;
				return _x_state;
			}
			/*!
			 * \brief To get the visual Y position, it's an easing transition for jump or bend and turn to the initial state at the end
			 */
			float getRealY(const int t)
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
					if(persoBbox[i] + obsBbox[i] == DETECT_COLLISION_VALUE) return true;
					i++;
				}
				return false;
			}
			~Personnage(){}
	};

	/*! \class World
	   * \brief
	   *	Group the gestion of all the entities of the game world
	   *  
	   */
	class World
	{
		private:
			float _t = 0; /*!< advance of the world*/
			float _speed = INITIAL_GAME_SPEED; /*!< Speed of the world*/
			unsigned int lastTile = -1; /*!< Save the last collided tile*/
			std::vector<Tile> _tiles; /*!< Vector of all tiles*/
			bool _randomized = false; /* True : the world will be generated, False : the world will be loaded from a file*/

			glm::mat4 _globalPosition; /*!< Save the global position of the world (because we choose to move the world and not the character*/
			glm::mat4 _globalRotation; /*!< Save the global rotation of the world, to update light position*/
			glm::mat4 _firstTileMatrix;

			Personnage *_perso;
			Library *_modelLib;
			Render *_render;

			SimpleAxeCam *_aroundCam; /*!< Camera to see around the character*/
			SimpleAxeCam *_eyesCam; /*!< First Person camera*/

			unsigned short int _activeCam = 0; /*!< Save the active Cam*/
		    bool rightClickDown = false; /*!< Keep the current state of the right click of the mouse to update cam*/
		    bool edit_mode = true; /*!< Used to lock or unlock the Camera edition*/
		    int lastX = 0, lastY = 0; /*!< Save the last mouse position to calculate the motion of the camera*/
		    int _currentBonus = -1; /*!< The current bonus*/
		    int _lastTimeBonus = 0; /*!< The global time of the last bonus taken*/

		    int _lastRotation = 0; /*!< The last rotation of the character, to smooth the camera movement*/
		    int _lastTimeRotation = 0;	/*!< The global time of the last rotation*/
		    int _timeToSmoothCamRotation = NB_FRAME_FOR_SMOOTH_CAM_ROTATION; /*!< Duration of camera smoothing for the rotation*/
		    int _timeStartGame = 0; /*!< The global time of the beginning of the last game*/

		    int _bonusInfluenceTime = NB_FRAME_FOR_BONUS_INFLUENCE; /*!< The time of the influence of the current bonus*/

		    int _nCoin = 0; /*!< Number of coin collected*/

		    int _beginningAnimDuration = NB_FRAME_FOR_BEGINNING_ANIMATION; /*!< Duration of the beginning animation*/
		    float _zoomBeginningAnimation = ZOOM_VALUE_FOR_BEGINNING_ANIMATION; /*!< Value of the camera zoom during the beginning animation*/

			int _beginningEndAnimation;
			bool _endAnimationStart = false;

		    std::vector<int> _bestScores;

			void loadFile(const std::string level); // Fill the vector _tiles with the file;

		public:
			World(const std::string file = "");
			
			/*!
			 * \brief Return a pointer of the current camera
			 */
			SimpleAxeCam* cam() const{
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
			int draw(const int global_time);
			
			/*!
			 * \brief Calculate the collision between the character and the current tile
			 */
			int collision(const int global_time, const int currentTile);
			
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
			void checkBonus(const int global_time);
			
			/*!
			 * \brief Set the current bonus if there is no current bonus anymore
			 */
			bool setBonus(const int b, const int global_time);

			
			/*!
			 * \brief Initialize the world
			 */
			void init(int global_time)
			{
				_render->reset();
				_timeStartGame = global_time;
				std::function<void(Tile &t)> resetTile = [](Tile &t){
					t.reset();
				};
				for_each(_tiles.begin(), _tiles.end(),resetTile);
				resume();
				_aroundCam->reset(DISTANCE_CAMERA_CHARACTER + _zoomBeginningAnimation,ANGLE_OF_CAMERA,0.0f);
				_globalPosition = glm::mat4();
				_globalRotation = glm::mat4();
				_currentBonus = -1;
				_t = 0.0;
				lastTile = -1;
				_activeCam = 0;
				_endAnimationStart = false;
			}
			
			/*!
			 * \brief Resume the game
			 */
			void resume() const
			{
				_render->use();
				glEnable(GL_DEPTH_TEST);
				_render->reset();
			}
			
			/*!
			 * \brief Close the game
			 */
			void close() const
			{
				_render->reset();
				glDisable(GL_DEPTH_TEST);
			}
			
			/*!
			 * \brief Add coins
			 */
			void addCoin(const int n)
			{
				_nCoin += n;
			}
			
			/*!
			 * \brief Return the number of coins collected
			 */
			int getCoin() const
			{
				return _nCoin;
			}
			
			/*!
			 * \brief Return the last score
			 */
			int getScore() const
			{
				return int(_t) * MULT_VALUE_FOR_SCORE;
			}
			
			/*!
			 * \brief Save the score in vector
			 */
			int saveScore()
			{
				int currentScore = getScore();
				int i = 0;
				while(i < _bestScores.size() && currentScore < _bestScores[i]) i++;
				_bestScores.insert(_bestScores.begin()+i,currentScore);
			}
			
			/*!
			 * \brief Return a pointer of the character
			 */
			Personnage* perso(){return _perso;}
			
			/*!
			 * \brief Get the mouse motion and change the cam thanks that
			 */
			void mouseMotion(const int x,const int y){
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
			void mouseButtonDown(const Uint8 btn){
			    if(btn == SDL_BUTTON_RIGHT) {
				rightClickDown = true;
				SDL_GetMouseState(&lastX, &lastY);
			    }
			    else if(btn == SDL_BUTTON_WHEELUP && edit_mode){
				cam()->moveFront(MOVE_FRONT_VALUE_ON_MOUSE_WHEEL);
			    }
			    else if(btn == SDL_BUTTON_WHEELDOWN && edit_mode){
				cam()->moveFront(-MOVE_FRONT_VALUE_ON_MOUSE_WHEEL);
			    }
			}
			
			/*!
			 * \brief Get the mouse button up event and process it
			 */
			void mouseButtonUp(const Uint8 btn){
			    if(btn == SDL_BUTTON_RIGHT) {
					rightClickDown = false;
			    }
			}
			
			/*!
			 * \brief Get the key button down event and process it
			 */
			void keyDown(const Uint8 key, const int t){
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
			void keyUp(const Uint8 key, const int t){
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
			void setLastRotation(const int way, const int global_time)
			{
				_lastRotation = way;
				_lastTimeRotation = global_time;
			}
			
			/*!
			 * \brief Return an angle to rotation the view matrix to smooth the camera motion at the world rotations
			 */
			float getSmoothCamAngle(const int global_time) const
			{
				int detlaT = global_time - _lastTimeRotation;
				if(detlaT > _timeToSmoothCamRotation) return 0.0;
				return -_lastRotation * (M_PI/2.0) * (1.0 - float(detlaT)/float(_timeToSmoothCamRotation));
			}
			float getEndAnimation(const int global_time) const
			{
				int deltaT = global_time - _beginningEndAnimation;
				if(deltaT < NB_FRAME_OF_END_ANIMATION)
				{
					return PERSO_ANGLE_END_ANIMATION * (deltaT / NB_FRAME_OF_END_ANIMATION);
				}
				return PERSO_ANGLE_END_ANIMATION;

			}
			~World(){
				delete _aroundCam;
				delete _eyesCam;
				delete _perso;
			}
	};
}

#endif

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
	class Personnage{
		private:
			int _id;
			int _x_state = 0; // -1 : left, 0 : middle, 1 : right
			int _y_state = 0; // 0 : normal, 1 : jump, -1 : down

			int _last_x_state = 0;

			int _last_x = 0; // last true x location
			int _last_y = 0; // last true y location
			int _points = 0;

			int nbFrameForSmoothTranslation = 10;
			int jumpTime = 50;

	 	public:

	 		Personnage(int id):_id(id){}
	 		void setId(int id){ _id = id;}
	 		int id()const{return _id;}
			
			void move_jump_bend(int state, int t){
				int deltaT = t-_last_y;
				if(deltaT > jumpTime)
				{
					_y_state = state;
					_last_y = t;
				}
			}
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

			float getRealX(int t)
			{
				int deltaT = t - _last_x;
				if(deltaT < nbFrameForSmoothTranslation) return (_x_state - _last_x_state)*sin(deltaT/float(nbFrameForSmoothTranslation) * M_PI/2) +_last_x_state;
				return _x_state;
			}
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

	class World
	{
		private:
			float _t = 0;
			float _speed = 0.15;
			unsigned int lastTile = -1;
			std::vector<Tile> _tiles;
			bool _randomized = false; // True : the world will be generated, False : the world will be loaded from a file

			glm::mat4 _globalPosition;
			glm::mat4 _globalRotation;
			glm::mat4 _firstTileMatrix;

			Personnage *_perso;
			Library *_modelLib;
			Render *_render;

			SimpleAxeCam *_aroundCam;
			SimpleAxeCam *_eyesCam;

			unsigned short int _activeCam = 0;
		    bool rightClickDown = false;
		    bool edit_mode = true;
		    int lastX = 0, lastY = 0;
		    int _currentBonus = -1;
		    int _lastTimeBonus = 0;

		    int _lastRotation = 0;
		    int _lastTimeRotation = 0;
		    int _timeToSmoothCamRotation = 30;
		    int _timeStartGame = 0;

		    int _bonusInfluenceTime = 300;

		    int _nCoin = 0;

		    int _beginningAnimDuration = 100;
		    float _zoomBeginningAnimation = 10;

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

			SimpleAxeCam* cam(){
				if(_activeCam == 0) return _aroundCam;
				return _eyesCam;
			}
			void changeCam(){
				if(_activeCam == 0) _activeCam = 1;
				else _activeCam = 0;
			}
			void addTile(Tile* t); // add tile at the endcqjkcdhsqhs hdgzusgz  zsgyzgs nina la meilleure de toutev
			int draw(int global_time);
			int collision(int global_time, int currentTile);
			void setLibrary(Library *lib){
				_modelLib = lib;
			}
			void setRender(Render *r){
				_render = r;
			}
			void checkBonus(int global_time);
			bool setBonus(int b, int global_time);

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
			void resume()
			{
				_render->use();
				glEnable(GL_DEPTH_TEST);
			}
			void close()
			{
				glDisable(GL_DEPTH_TEST);
			}
			void addCoin(int n)
			{
				_nCoin += n;
			}
			int getCoin()
			{
				return _nCoin;
			}
			int getScore()
			{
				return int(_t) * 100;
			}
			Personnage* perso(){return _perso;}

			void mouseMotion(int x,int y){
	            if(rightClickDown && edit_mode){
	                cam()->rotateLeft(y-lastY);
	                cam()->rotateTop(x-lastX);
	                lastX = x;
	                lastY = y;
	            }
			}
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
			void mouseButtonUp(Uint8 btn){
	            if(btn == SDL_BUTTON_RIGHT) {
	                rightClickDown = false;
	            }
			}
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
	        void setLastRotation(int way, int global_time)
	        {
		    	_lastRotation = way;
		    	_lastTimeRotation = global_time;
	        }
	        float getSmoothCamAngle(int global_time)
	        {
	        	int detlaT = global_time - _lastTimeRotation;
	        	if(detlaT > _timeToSmoothCamRotation) return 0.0;
	        	return -_lastRotation * (M_PI/2.0) * (1.0 - float(detlaT)/float(_timeToSmoothCamRotation));
	        }
	};
}

#endif

#ifndef _LIB_IMPORT_GAME_IMAC_LSM
#define _LIB_IMPORT_GAME_IMAC_LSM
#pragma once

#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <glimac/TrackballCamera.hpp>

class Personnage{
	private:
		Model _model;
		int _x_state = 0; // -1 : left, 0 : middle, 1 : right

		float _x_real = 0; // the true x location
		float _y_real = 0; // the true y location
		float _state = 0; // 0 : normal, 1 : jump, 2 : down
		int _points = 0;

 	public:

 		Personnage(Model m):_model(m){}
 		void draw() const;
};

class Bonus {
	private:
		int id;
		// + lambda fonction pour coder le comportement
};

class Obstacle {
	private:
		int _model;
		int _posX;
		std::vector<int> _bbox;
	
	public:
		void setBbox(){
			if(_model == 0){ //Ketchup
				if(_posX == 0){
					_bbox.insert(_bbox.end(),{1,0,0,1,0,0,1,0,0});
				}
				else if(_posX == 1){
					_bbox.insert(_bbox.end(),{0,1,0,0,1,0,0,1,0});
				}
				else if(_posX == 2){
					_bbox.insert(_bbox.end(),{0,0,1,0,0,1,0,0,1});
				}
			}
			else if(_model == 1){ //Moutarde
				if(_posX == 0){
					_bbox.insert(_bbox.end(),{1,1,0,1,1,0,0,0,0});
				}
				else if(_posX == 1){
					_bbox.insert(_bbox.end(),{0,1,1,0,1,1,0,0,0});
				}
			}
			else if(_model == 2){ //Conserve
				_bbox.insert(_bbox.end(),{1,0,1,1,1,1,1,1,1});
			}
			else if(_model == 3){ //Jus
				_bbox.insert(_bbox.end(),{1,1,1,0,0,0,0,0,0});
			}
		}
		
};

class Tile{
	public:
		int _support; // id of the model in the Library
	
		int _obstacle; // id of the model in the Library
		int _x_obs; // pos x obs
	
		int _bonus; // id of the model in the Library
		int _x_bonus; // pos x bonus
		int _y_bonus; // pos y bonus
	
		int _x_coin; // pos x coin
		int _y_coin; // pos y coin
		Tile(int s,int o,int ox,int b,int bx,int by,int cx,int cy)
			:_support(s),_obstacle(o), _x_obs(ox), _bonus(b), _x_bonus(bx),_y_bonus(by), 
			_x_coin(cx), _y_coin(cy){}
};

class Support{
	private:
		int id;
};

class Library {
	private:
		std::vector<Model> _persos;
		std::vector<Model> _supports;
		std::vector<Model> _obstacles;
		std::vector<Model> _bonus;
		Model _coin;

	public:
		Library(Model coin);
		void addPerso(Model m){
			_persos.push_back(m);
		}
		void addSupport(Model m){
			_supports.push_back(m);
		}
		void addBonus(Model m){
			_bonus.push_back(m);
		}
		void addObstacle(Model m){
			_obstacles.push_back(m);
		}
		void setCoin(Model m){_coin = m;};
		Model perso(unsigned int i) const {return _persos[i];}
		Model support(unsigned int i) const {return _supports[i];}
		Model bonus(unsigned int i) const {return _bonus[i];}
		Model obstacle(unsigned int i) const {return _obstacles[i];}
		Model coin() const {return _coin;}

		int nPerso() const {return _persos.size();}
		int nSupport() const {return _supports.size();}
		int nBonus() const {return _bonus.size();}
		int nObstacle() const {return _obstacles.size();}
};

class Render {

	private:

	    // Uniform variable

	    GLuint _uMVPMatrix;
	    GLuint _uMVMatrix;
	    GLuint _uNormalMatrix;

	    GLuint _uKd;
	    GLuint _uKs;
	    GLuint _uShininess;
	    GLuint _uLightPos_vs;
	    GLuint _uLightIntensity;

		// Light parameters

		glm::vec3 _Kd = glm::vec3(0.5,0.5,0.5);
		glm::vec3 _Ks = glm::vec3(0.5,0.5,0.5);
		float _Shininess = 0.5;
		glm::vec4 _LightPos_vs = glm::vec4(2.0,2.0,2.0,0.0);
		glm::vec3 _LightIntensity = glm::vec3(2.0,2.0,2.0);

	public:

	    glimac::Program _prog;

	    // Definition of Matrix

		glm::mat4 _projMatrix = glm::perspective(glm::radians(70.f),8.0f/6.0f,0.1f,100.f);

		Render(std::string vertexShader, std::string fragmentShader){

			_prog = glimac::loadProgram(vertexShader, fragmentShader);

			// Set uniform variables

		    _uMVPMatrix = glGetUniformLocation(_prog.getGLId(),"uMVPMatrix");
		    _uMVMatrix = glGetUniformLocation(_prog.getGLId(),"uMVMatrix");
		    _uNormalMatrix = glGetUniformLocation(_prog.getGLId(),"uNormalMatrix");

		    _uKd = glGetUniformLocation(_prog.getGLId(),"uKd");
		    _uKs = glGetUniformLocation(_prog.getGLId(),"uKs");
		    _uShininess = glGetUniformLocation(_prog.getGLId(),"uShininess");
		    _uLightPos_vs = glGetUniformLocation(_prog.getGLId(),"uLightPos_vs");
		    _uLightIntensity = glGetUniformLocation(_prog.getGLId(),"uLightIntensity");

		    _prog.use();
		}
		void reset() const {
        	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        }
        void sendLight(glm::mat4 viewMatrix) const {
	        glUniform3fv(_uKd,1,glm::value_ptr(_Kd));
	        glUniform3fv(_uKs,1,glm::value_ptr(_Ks));
	        glUniform1f(_uShininess,_Shininess);
	        glUniform3fv(_uLightPos_vs,1,glm::value_ptr(viewMatrix*_LightPos_vs));
	        glUniform3fv(_uLightIntensity,1,glm::value_ptr(_LightIntensity));
		}
        void sendMatrix(glm::mat4 MVMatrix) const {
	    	glUniformMatrix4fv(_uMVPMatrix,1,GL_FALSE,glm::value_ptr(_projMatrix*MVMatrix));
	    	glUniformMatrix4fv(_uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
	    	glUniformMatrix4fv(_uNormalMatrix,1,GL_FALSE,glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
		}
};

class World
{
	private:
		float _z = 0; // Global position in the word
		unsigned int lastTile = -1;
		std::vector<Tile> _tiles;
		int _t = 0; // Time elapsed from the beginning of the game
		bool _randomized = false; // True : the world will be generated, False : the world will be loaded from a file

		glm::mat4 _globalMVMatrix;

		int _currentPerso = 0;

		Library *_modelLib;

		Render *_render;

		SimpleAxeCam* _aroundCam;
		SimpleAxeCam* _eyesCam;

		unsigned short int _activeCam = 0; 

		void loadFile(std::string level); // Fill the vector _tiles with the file;
	public:
		World(std::string file = ""){
			if(file == "") _randomized = true;
			else loadFile(file);
			_aroundCam = new TrackballCamera(7.0f,25.0f,0.0f);
     		_eyesCam = new EyesCam(30.0f,0.0f);
     		_eyesCam->setPosition(glm::vec3(5.0f,-1.2f,0.2f));
		}

		SimpleAxeCam* cam(){
			if(_activeCam == 0) return _aroundCam;
			return _eyesCam;
		}
		void changeCam(){
			if(_activeCam == 0) _activeCam = 1;
			else _activeCam = 0;
		}
		void addTile(Tile &t); // add tile at the end
		void draw();
		void setLibrary(Library *lib){
			_modelLib = lib;
		}
		void setRender(Render *r){
			_render = r;
		}
};

#endif

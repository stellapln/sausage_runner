#ifndef _LIB_IMPORT_GAME_IMAC_LSM
#define _LIB_IMPORT_GAME_IMAC_LSM
#pragma once

#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>

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

class Tile
{
	private:
		int _model; // id of the model in the Library
		int _bonus; // -1 : no bonus, 0, ... index in a bonus tab
		int _coin; // number of coins in the tile
	public:
		Tile(int m, int b = -1, int c = 0):_model(m), _bonus(b), _coin(c){}
};
class Library {
	private:
		std::vector<Model> _persos;
		std::vector<Model> _tiles;
		std::vector<Model> _obstacles;
		std::vector<Model> _bonus;
		Model _coin;

	public:
		Library();
		void addPerso(Model m){
			_persos.push_back(m);
		}
		void addTile(Model m){
			_tiles.push_back(m);
		}
		void addBonus(Model m){
			_bonus.push_back(m);
		}
		void setCoin(Model m);
		Model perso(unsigned int i) const {return _persos[i];}
		Model tile(unsigned int i) const {return _tiles[i];}
		Model bonus(unsigned int i) const {return _bonus[i];}
		Model coin() const {return _coin;}
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
		glm::vec3 _LightIntensity = glm::vec3(20.0,20.0,20.0);

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
		std::deque<Tile> _tiles;
		int _t = 0; // Time elapsed from the beginning of the game
		bool _randomized = false; // True : the world will be generated, False : the world will be loaded from a file

		FreeflyCamera _eyes;
		// TrackballCamera around;

		glm::mat4 globalMVMatrix;

		int _currentPerso = 0;

		Library _modelLib;

		std::vector<Bonus> _bonusVec; // stock the Bonus models
		std::vector<Tile> _tileVec; // stock the Tiles model

		//Render _render;

		void loadFile(std::string file); // Fill the vector _tiles with the file;
	public:
		World(std::string file = ""){
			if(file == "") _randomized = true;
			else loadFile(file);
		}

		void removeTile(); // remove the first tile
		void addTile(Tile &t); // add tile at the end
		void draw() const;
		void addBonusModel(Bonus &b){_bonusVec.push_back(b);}
		void addTileModel(Tile &t){_tileVec.push_back(t);}
		void setLibrary(Library lib){
			_modelLib = lib;
		}
		
		Bonus getBonusModel(unsigned int i) const {
			// TODO : Exception if(i > _bonusVec.size()) trow ...
			return _bonusVec[i];
		}
		Tile getTileModel(unsigned int i) const {
			// TODO : Exception if(i > _tileVec.size()) trow ...
			return _tileVec[i];
		}
};

#endif
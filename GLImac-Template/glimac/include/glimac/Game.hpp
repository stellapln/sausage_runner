#ifndef _LIB_IMPORT_GAME_IMAC_LSM
#define _LIB_IMPORT_GAME_IMAC_LSM
#pragma once

#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/Library.hpp>
#include <glimac/Render.hpp>

class Personnage{
	private:
		int _id;
		int _x_state = 0; // -1 : left, 0 : middle, 1 : right
		int _y_state = 0; // 0 : normal, 1 : jump, 2 : down

		float _x_real = 0; // the true x location
		float _y_real = 0; // the true y location
		int _points = 0;

 	public:

 		Personnage(int id):_id(id){}
 		void setId(int id):_id(id){}
 		int id(){return id;}
};

class World
{
	private:
		float _t = 0;
		float _speed = 0.2;
		unsigned int lastTile = -1;
		std::vector<Tile> _tiles;
		bool _randomized = false; // True : the world will be generated, False : the world will be loaded from a file

		glm::mat4 _globalPosition;
		glm::mat4 _globalRotation;

		Personnage* _perso;

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
		void addTile(Tile &t); // add tile at the end
		void draw();
		void setLibrary(Library *lib){
			_modelLib = lib;
		}
		void setRender(Render *r){
			_render = r;
		}
		Personnage* perso(){return _perso;}
};

#endif

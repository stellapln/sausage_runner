#include <glimac/SDLWindowManager.hpp>
#include <iostream>
#include <glimac/glm.hpp>
#include <random>
#include <cmath>
#include <queue>
#include <string>
#include <cstring>
#include <functional>
#include <glimac/FreeflyCamera.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glimac/Model.hpp>
#include <glimac/Game.hpp>
#include <stdio.h>

#define NB_COIN_BY_TILE 3
#define SIZE_OF_TILE 3.0

void World::loadFile(const std::string level){
	std::string levelName = level;
	FILE *file = fopen(levelName.c_str(), "r");
  	if(!file){
   		std::cout << "Error : load fichier" << std::endl;
  	}

  	int sup, obs, xo, bon, xb, yb, xp, yp;

	while(fscanf(file, "%d %d %d %d %d %d %d %d", &sup, &obs, &xo, &bon, &xb, &yb, &xp, &yp) != EOF){
    	Tile new_tile(sup, obs, xo, bon, xb, yb, xp, yp);
    	addTile(new_tile);
	}
}

void World::addTile(Tile &t){
	_tiles.push_back(t);
}
void World::draw() {
    glm::mat4 MVMatrix = _globalMVMatrix;
    glm::mat4 MVMatrixModified;
    _render->reset();
	glm::mat4 viewMatrix;
	if(_activeCam == 0)
		viewMatrix = _aroundCam->getMatrixView();
	else
		viewMatrix = _eyesCam->getMatrixView();
    MVMatrix = viewMatrix*MVMatrix;

    _render->sendLight(viewMatrix);

    MVMatrixModified = glm::translate(MVMatrix, glm::vec3(0, fabs(sinf(_z))/2.0,0));

    _render->sendMatrix(MVMatrixModified);
    _modelLib->perso(_currentPerso).draw();

    MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, SIZE_OF_TILE+_z));
	MVMatrix = MVMatrix;
    // Models
        
	/* Affichage des tuiles */ // À faire une fois que la class Tiles sera prete

	for(int i = 0;i < _tiles.size();i++)
	{
    	MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, -SIZE_OF_TILE));
    	_render->sendMatrix(MVMatrix);
    	if(_tiles[i]._support < _modelLib->nSupport())
    	{
    		_modelLib->support(_tiles[i]._support).draw();
    	}
    	else if(_tiles[i]._support == _modelLib->nSupport())
    	{
    		_modelLib->support(0).draw();
    		MVMatrix = glm::rotate(MVMatrix, float(-M_PI/2.0), glm::vec3(0, 1.0, 0));
    	}
    	else if(_tiles[i]._support == _modelLib->nSupport()+1)
    	{
    		_modelLib->support(0).draw();
    		MVMatrix = glm::rotate(MVMatrix, float(M_PI/2.0), glm::vec3(0, 1.0, 0));
    	}

    	MVMatrixModified = glm::translate(MVMatrix, glm::vec3(-SIZE_OF_TILE/2.0 + float(_tiles[i]._x_obs), 0, 0));
    	_render->sendMatrix(MVMatrixModified);

    	if(_tiles[i]._obstacle < _modelLib->nObstacle())
    		_modelLib->obstacle(_tiles[i]._obstacle).draw();

    	MVMatrixModified = glm::translate(MVMatrix, glm::vec3(-SIZE_OF_TILE/2.0+ float(_tiles[i]._x_bonus), float(_tiles[i]._y_bonus),0.0));
    	_render->sendMatrix(MVMatrixModified);

    	if(_tiles[i]._bonus < _modelLib->nBonus())
    		_modelLib->bonus(_tiles[i]._bonus).draw();

    	if(_tiles[i]._x_coin != 5 && _tiles[i]._y_coin != 5)
    	{
	    	MVMatrixModified = glm::translate(MVMatrix, glm::vec3(-SIZE_OF_TILE/2.0 + float(_tiles[i]._x_coin), float(_tiles[i]._y_coin),-SIZE_OF_TILE/2.0));
	    	int j = 0;
	    	for(j = 0;j < NB_COIN_BY_TILE;j++)
	    	{
		    	MVMatrixModified = glm::translate(MVMatrixModified, glm::vec3(0.0,0.0,float(SIZE_OF_TILE/NB_COIN_BY_TILE)));
	    		_render->sendMatrix(MVMatrixModified);
	    		_modelLib->coin().draw();
	    	}
	    }

	    unsigned int currentTile = int(_z/SIZE_OF_TILE);
	    if(currentTile != lastTile)
	    {
	    	if(_tiles[currentTile]._support == _modelLib->nSupport()){
	    		_globalMVMatrix = glm::rotate(_globalMVMatrix, float(-M_PI/2.0), glm::vec3(0, 1.0, 0));
	    	}
	    	else if(_tiles[currentTile]._support == _modelLib->nSupport()+1){
	    		_globalMVMatrix = glm::rotate(_globalMVMatrix, float(M_PI/2.0), glm::vec3(0, 1.0, 0));
	    	}
	    	lastTile = currentTile;
	    }
	    _z+=0.004;
	}
}
void Personnage::draw() const{
	_model.draw();
}
Library::Library(Model coin):_coin(coin){}

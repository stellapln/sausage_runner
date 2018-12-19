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

std::vector<int> Personnage::getBbox(){
    std::vector<int> bbox;
	if(_x_state == -1){ 
		if(_y_state == -1){
			bbox.insert(bbox.end(),{1,0,0,0,0,0,0,0,0});	
		}
		else if(_y_state == 0){
			bbox.insert(bbox.end(),{1,0,0,1,0,0,0,0,0});	
		}
		else {	
			bbox.insert(bbox.end(),{0,0,0,0,0,0,1,0,0});
		}
	}
	else if(_x_state == 0){ 
		if(_y_state == -1){
			bbox.insert(bbox.end(),{0,1,0,0,0,0,0,0,0});	
		}
		else if(_y_state == 0){
			bbox.insert(bbox.end(),{0,1,0,0,1,0,0,0,0});	
		}
		else {	
			bbox.insert(bbox.end(),{0,0,0,0,0,0,0,1,0});
		}
	}
	else { 
		if(_y_state == -1){
			bbox.insert(bbox.end(),{0,0,1,0,0,0,0,0,0});	
		}
		else if(_y_state == 0){
			bbox.insert(bbox.end(),{0,0,1,0,0,1,0,0,0});	
		}
		else {
			bbox.insert(bbox.end(),{0,0,0,0,0,0,0,0,1});
		}
	}
    return bbox;
}

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

bool World::draw(int global_time) {
    glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0,0,0));
    glm::mat4 MVMatrixModified;
	glm::mat4 viewMatrix;

    _render->reset();

	if(_activeCam == 0)
		viewMatrix = _aroundCam->getMatrixView();
	else
		viewMatrix = _eyesCam->getMatrixView();
    MVMatrix = viewMatrix*MVMatrix;

    // Skybox

 	MVMatrixModified = glm::scale(MVMatrix,glm::vec3(10.0,10.0,10.0));
    _render->sendMatrix(MVMatrixModified);
    _modelLib->skybox(0).draw();

    // Lights

    _render->sendLight(viewMatrix*_globalRotation);

    // Personnage

    if(_perso->get_y_state() == 0)
    {
        MVMatrix = glm::translate(MVMatrix, glm::vec3(0, fabs(sinf(_t))/2.0,0));
    }
    else if(_perso->get_y_state() == -1)
    {
        MVMatrix = glm::rotate(MVMatrix, glm::radians(80.0f),glm::vec3(1, 0,0));
        MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0.0,0));
    }
    MVMatrix = glm::translate(MVMatrix, glm::vec3(_perso->get_x_state(),_perso->get_y_state() ,0.0));
    
    _render->sendMatrix(MVMatrix);
    _modelLib->perso(_perso->id()).draw();

    MVMatrix = _globalPosition;
    MVMatrix = viewMatrix*MVMatrix;

	for(int i = 0;i < _tiles.size();i++)
	{
    	MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, -SIZE_OF_TILE));
    	_render->sendMatrix(MVMatrix);
    	if(_tiles[i]._support.id() < _modelLib->nSupport()) // Affichage des supports
    	{
    		_modelLib->support(_tiles[i]._support.id()).draw();
    	}
    	else if(_tiles[i]._support.id() == _modelLib->nSupport()) // Virage à droite
    	{
    		_modelLib->support(0).draw();
    		MVMatrix = glm::rotate(MVMatrix, glm::radians(-90.0f), glm::vec3(0, 1.0, 0));
    	}
    	else if(_tiles[i]._support.id() == _modelLib->nSupport()+1) // Virage à gauche
    	{
    		_modelLib->support(0).draw();
    		MVMatrix = glm::rotate(MVMatrix, glm::radians(90.0f), glm::vec3(0, 1.0, 0));
    	}

    	MVMatrixModified = glm::translate(MVMatrix, glm::vec3(-SIZE_OF_TILE/2.0 + float(_tiles[i]._obstacle.x()), 0, 0));
    	_render->sendMatrix(MVMatrixModified);

    	if(_tiles[i]._obstacle.id() < _modelLib->nObstacle()) // Affichage des obstacles
    		_modelLib->obstacle(_tiles[i]._obstacle.id()).draw();

    	MVMatrixModified = glm::translate(MVMatrix, glm::vec3(-SIZE_OF_TILE/2.0+ float(_tiles[i]._bonus.x()), float(_tiles[i]._bonus.y()),0.0));
    	_render->sendMatrix(MVMatrixModified);

    	if(_tiles[i]._bonus.id() < _modelLib->nBonus()) // Affichage des bonus
    		_modelLib->bonus(_tiles[i]._bonus.id()).draw();

    	if(_tiles[i]._coin.x() != 5 && _tiles[i]._coin.x() != 5) // Affichage des pieces
    	{
	    	MVMatrixModified = glm::translate(MVMatrix, glm::vec3(-SIZE_OF_TILE/2.0 + float(_tiles[i]._coin.x()), float(_tiles[i]._coin.y()),-SIZE_OF_TILE/2.0));
	    	int j = 0;
	    	for(j = 0;j < NB_COIN_BY_TILE;j++)
	    	{
		    	MVMatrixModified = glm::translate(MVMatrixModified, glm::vec3(0.0,0.0,float(SIZE_OF_TILE/NB_COIN_BY_TILE)));
	    		_render->sendMatrix(MVMatrixModified);
	    		_modelLib->coin().draw();
	    	}
	    }
	}

    _t+=_speed;
    unsigned int currentTile = int(_t/int(SIZE_OF_TILE) - int(SIZE_OF_TILE)/2);
    if(currentTile < _tiles.size())
    {
        if(_tiles[currentTile]._obstacle.id() < _modelLib->nObstacle() &&  _perso->collide(&(_tiles[currentTile]._obstacle))){
            return false;
        }

        if(_tiles[currentTile]._bonus.id() < _modelLib->nBonus() &&  _perso->collide(&(_tiles[currentTile]._bonus))){
            //bonus
        }

        if(_perso->collide(&(_tiles[currentTile]._coin))){
            //pieces++
        }
        
        if(_tiles[currentTile]._support.id() < _modelLib->nSupport()+3 &&  _perso->collide(&(_tiles[currentTile]._support))){
            return false;
        }

        _globalPosition = glm::translate(glm::mat4(), glm::vec3(0, 0, _speed))*_globalPosition;

        if(currentTile != lastTile)
        {
        	if(_tiles[currentTile]._support.id() == _modelLib->nSupport()){
        		_globalPosition = glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(0, 1.0, 0))*_globalPosition;
        		_globalRotation = glm::rotate(_globalRotation, glm::radians(90.0f), glm::vec3(0, 1.0, 0));
        	}
        	else if(_tiles[currentTile]._support.id() == _modelLib->nSupport()+1){
        		_globalPosition = glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(0, 1.0, 0))*_globalPosition;
        		_globalRotation = glm::rotate(_globalRotation, glm::radians(-90.0f), glm::vec3(0, 1.0, 0));
        	}
        	lastTile = currentTile;
        }
    }
    return true;
} //https://github.com/stellapln/sausage_runner
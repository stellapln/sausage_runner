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

using namespace sausageRunner;

#define NB_COIN_BY_TILE 3
#define SIZE_OF_TILE 3.0

#define TILE_DELETE_BEFORE 2
#define TILE_SEE_AFTER 20

#define BONUS_AIMANT 0
#define BONUS_SHIELD 1
#define BONUS_X2 2

#define SPECIAL_PROTECT 0
#define SPECIAL_POIRE 1
#define SPECIAL_ARRIVE 2

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


World::World(std::string file){
    if(file == "")
    {  
        _randomized = true;
    }
    else
    {
        try
        {
            loadFile(file);
        }
        catch(Except err)
        {
            std::cerr << err.what() << std::endl;
        }
    }
    _aroundCam = new TrackballCamera(5.0f + _zoomBeginningAnimation,25.0f,0.0f);
    _eyesCam = new EyesCam(30.0f,0.0f);
    _eyesCam->setPosition(glm::vec3(0.0f,-1.4f,0.2f));
    _perso = new Personnage(0);
}

void World::loadFile(const std::string level){
	std::string levelName = level;
    std::cout << levelName << std::endl;
	FILE *file = fopen(levelName.c_str(), "r");
  	if(!file){
   		throw Except("Level file not loaded",__FILE__,__LINE__);
  	}

  	int sup, obs, xo, bon, xb, yb, xp, yp;
	while(fscanf(file, "%d %d %d %d %d %d %d %d", &sup, &obs, &xo, &bon, &xb, &yb, &xp, &yp) != EOF){
    	//Tile* new_tile = new Tile(sup, obs, xo, bon, xb, yb, xp, yp);
    	addTile(new Tile(sup, obs, xo, bon, xb, yb, xp, yp));
	}
    fclose(file);
}

void World::addTile(Tile* t){
	_tiles.push_back(*t);
}


int World::collision(int global_time, int currentTile)
{
    int middleHit = int(_t/int(SIZE_OF_TILE)-1);
    if(currentTile < _tiles.size())
    {
        if(_currentBonus != BONUS_SHIELD){
            if(_tiles[currentTile]._obstacle.id() < _modelLib->nObstacle() &&  _perso->collide(&(_tiles[currentTile]._obstacle))){
                return 3;
            }
        }

        if(_tiles[currentTile]._bonus.id() < _modelLib->nBonus() &&  _perso->collide(&(_tiles[currentTile]._bonus))){
            if(setBonus(_tiles[currentTile]._bonus.id(),global_time))
                _tiles[currentTile].takeBonus();
        }

        if(_tiles[currentTile].haveCoin() && (_perso->collide(&(_tiles[currentTile]._coin)) || _currentBonus == BONUS_AIMANT)){
            int factorCoins = 1;
            if(_currentBonus == BONUS_X2) factorCoins = 2;
            addCoin(NB_COIN_BY_TILE * factorCoins);
            _tiles[currentTile].takeCoin();
        }
        _globalPosition = glm::translate(glm::mat4(), glm::vec3(0, 0, _speed))*_globalPosition;

        if(middleHit != lastTile)
        {
            if(_currentBonus != BONUS_SHIELD) {
                if(_tiles[currentTile]._support.id() < _modelLib->nSupport()+3 &&  _perso->collide(&(_tiles[currentTile]._support))){
                    return 3;
                }
            }
            if(_tiles[middleHit]._support.id() == _modelLib->nSupport()){
                _globalPosition = glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(0, 1.0, 0))*_globalPosition;
                _globalRotation = glm::rotate(_globalRotation, glm::radians(90.0f), glm::vec3(0, 1.0, 0));
                setLastRotation(1,global_time);
            }
            else if(_tiles[middleHit]._support.id() == _modelLib->nSupport()+1){
                _globalPosition = glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(0, 1.0, 0))*_globalPosition;
                _globalRotation = glm::rotate(_globalRotation, glm::radians(-90.0f), glm::vec3(0, 1.0, 0));
                setLastRotation(-1,global_time);
            }
            lastTile = middleHit;

            if(currentTile == _tiles.size()-1)
            {
                return 3;
            }
        }
    }
    return 1;
}

int World::draw(int global_time) {
    glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0,0,0));
    glm::mat4 MVMatrixModified;
    glm::mat4 MVMatrixModifiedM;
	glm::mat4 viewMatrix;

    //if(global_time%200 == 0) _render->addLight(new Light(glm::vec3(0.0,1.0,0.0),50.0,1));

    int deltaT = global_time - _timeStartGame;

    _render->reset();

	if(_activeCam == 0)
    {
		viewMatrix = _aroundCam->getMatrixView();// * getSmoothCamAngle(global_time);
        viewMatrix = glm::rotate(viewMatrix, getSmoothCamAngle(global_time),glm::vec3(0.0,1.0,0.0));
    }
	else viewMatrix = _eyesCam->getMatrixView();

    MVMatrix = viewMatrix*MVMatrix;

    // Current Bonus

    if(_currentBonus >= 0)
    {
        MVMatrixModified = glm::translate(MVMatrix,glm::vec3(0,2.0,0));
        MVMatrixModified = glm::rotate(MVMatrixModified,sinf(_t*0.2),glm::vec3(0,1.0,0));
        MVMatrixModified = glm::scale(MVMatrixModified,glm::vec3(0.5,0.5,0.5));
        _render->sendMatrix(MVMatrixModified);
        _modelLib->bonus(_currentBonus).draw();
    }

    // Skybox

 	MVMatrixModified = glm::scale(MVMatrix,glm::vec3(50.0,50.0,50.0));
    _render->sendMatrix(MVMatrixModified);
    _modelLib->skybox(0).draw();

    // Lights

    _render->sendLight(viewMatrix*_globalRotation);

    // Poire

    MVMatrixModified = glm::translate(MVMatrix,glm::vec3(0.0,0.0,4.5));
    MVMatrixModified = glm::rotate(MVMatrixModified,sinf(global_time*0.1),glm::vec3(0.0,1.0,0.5));
    _render->sendMatrix(MVMatrixModified);
    _modelLib->special(SPECIAL_POIRE).draw();

    // Personnage

    float persoRealX = _perso->getRealX(global_time);
    float persoRealY = _perso->getRealY(global_time);

    if(_perso->get_y_state() == 0)
    {
        MVMatrix = glm::translate(MVMatrix, glm::vec3(0, fabs(sinf(_t))*0.3,0));
    }
    else if(_perso->get_y_state() == -1)
    {
        MVMatrix = glm::rotate(MVMatrix, glm::radians(80.0f),glm::vec3(1, 0,0));
    }
    if(_activeCam == 0) MVMatrix = glm::translate(MVMatrix, glm::vec3(persoRealX,persoRealY ,0.0));
    
    _render->sendMatrix(MVMatrix);
    _modelLib->perso(_perso->id()).draw();


    MVMatrix = _globalPosition;
    if(_activeCam == 1)viewMatrix = glm::translate(viewMatrix, glm::vec3(-persoRealX,-persoRealY,0.0));

    MVMatrix = viewMatrix*MVMatrix;

    int currentTile = int(_t/int(SIZE_OF_TILE) - 0.5);
    int firstTileDisplay = std::max(0,currentTile - TILE_DELETE_BEFORE);
    int lastTileDisplay = std::min(currentTile + TILE_SEE_AFTER, int(_tiles.size()));

	for(int i = 0;i < lastTileDisplay;i++)
	{
    	MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, -SIZE_OF_TILE));

        if(i <= firstTileDisplay)
        {
            if(_tiles[i]._support.id() == _modelLib->nSupport()) MVMatrix = glm::rotate(MVMatrix, glm::radians(-90.0f), glm::vec3(0, 1.0, 0));
            else if(_tiles[i]._support.id() == _modelLib->nSupport()+1) MVMatrix = glm::rotate(MVMatrix, glm::radians(90.0f), glm::vec3(0, 1.0, 0));
        }
        else
        {
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
            if(_tiles[i]._support.id() > 0 && _currentBonus == BONUS_SHIELD) _modelLib->special(0).draw();


        	MVMatrixModified = glm::translate(MVMatrix, glm::vec3(-SIZE_OF_TILE/2.0 + float(_tiles[i]._obstacle.x()), 0, 0));
        	_render->sendMatrix(MVMatrixModified);

        	if(_tiles[i]._obstacle.id() < _modelLib->nObstacle()) // Affichage des obstacles
        		_modelLib->obstacle(_tiles[i]._obstacle.id()).draw();

        	MVMatrixModified = glm::translate(MVMatrix, glm::vec3(-SIZE_OF_TILE/2.0+ float(_tiles[i]._bonus.x())+0.5, float(_tiles[i]._bonus.y()),0.0));
            MVMatrixModified = glm::rotate(MVMatrixModified, global_time*0.05f,glm::vec3(0.0,1.0,0.0));
           // MVMatrixModified = glm::translate(MVMatrixModified, global_time*0.05f,glm::vec3(0.0,1.0,0.0)); /* ICI */
            _render->sendMatrix(MVMatrixModified);

        	if(_tiles[i].haveBonus() && _tiles[i]._bonus.id() < _modelLib->nBonus()) // Affichage des bonus
            {
        		_modelLib->bonus(_tiles[i]._bonus.id()).draw();
            }

        	if(_tiles[i].haveCoin()) // Affichage des pieces
        	{
    	    	MVMatrixModified = glm::translate(MVMatrix, glm::vec3(-SIZE_OF_TILE/2.0 + float(_tiles[i]._coin.x())+0.5, float(_tiles[i]._coin.y()),-SIZE_OF_TILE/2.0));
    	    	int j = 0;
    	    	for(j = 0;j < NB_COIN_BY_TILE;j++)
    	    	{
    		    	MVMatrixModified = glm::translate(MVMatrixModified, glm::vec3(0.0,0.0,float(SIZE_OF_TILE/NB_COIN_BY_TILE)));
    	    		MVMatrixModifiedM = glm::rotate(MVMatrixModified, global_time*0.1f,glm::vec3(0.0,1.0,0.0));
                    _render->sendMatrix(MVMatrixModifiedM);
    	    		_modelLib->coin().draw();
    	    	}
    	    }
            if(i == _tiles.size()-1)
            {
                _render->sendMatrix(MVMatrix);
                _modelLib->special(SPECIAL_ARRIVE).draw();
            }
        }
	}
    if(deltaT < _beginningAnimDuration)_aroundCam->moveFront(_zoomBeginningAnimation/_beginningAnimDuration);
    _t+=_speed;
    checkBonus(global_time);
    return collision(global_time, currentTile);
}

bool World::setBonus(int b, int global_time)
{
    if(_currentBonus == -1)
    {
        _currentBonus = b;
        _lastTimeBonus = global_time;
        return true;
    }
    return false;
}
void World::checkBonus(int global_time){
    if(global_time - _lastTimeBonus > _bonusInfluenceTime)
    {
        _currentBonus = -1;
    }
}
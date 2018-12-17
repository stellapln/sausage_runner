#include <glimac/SDLWindowManager.hpp>
#include <iostream>
#include <glimac/glm.hpp>
#include <random>
#include <queue>
#include <functional>
#include <glimac/FreeflyCamera.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glimac/Model.hpp>
#include <glimac/Game.hpp>

void World::loadFile(const std::string file){}

void World::removeTile(){
	_tiles.pop_front();
}
void World::addTile(Tile &t){
	_tiles.push_back(t);
}
void World::draw() const {
    glm::mat4 MVMatrix = glm::translate(globalMVMatrix, glm::vec3(0, 0, 0));
    _render->reset();
	glm::mat4 viewMatrix;
	if(_activeCam == 0)
		viewMatrix = _aroundCam.getMatrixView();
	else
		viewMatrix = _eyesCam.getMatrixView();
    MVMatrix = viewMatrix*MVMatrix;

    _render->sendLight(viewMatrix);

    _render->sendMatrix(MVMatrix);
    _modelLib->perso(_currentPerso).draw();

    _modelLib->support(2).draw();

    // Models
    //_render.sendMatrix(MVMatrix);
        
	/* Affichage des tuiles */ // À faire une fois que la class Tiles sera prete

	/*std::function <void (const Tile &)> worldDrawTile = [MVMatrix](const Tile &t){
		// t.draw();
	};
	std::for_each(_tiles.begin(),_tiles.end(),worldDrawTile);*/
}
void Personnage::draw() const{
	_model.draw();
}
Library::Library(Model coin):_coin(coin){}
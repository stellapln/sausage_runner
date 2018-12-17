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
	
    MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0)); 
	/*viewMatrix = cam.getMatrixView(); // Get the view Matrix from the camera

    render.reset();
    render.sendLight(viewMatrix);
    MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0)); 
    // Models
    MVMatrix = viewMatrix*MVMatrix;
    render.sendMatrix(MVMatrix);

    perso.draw();/*
        
	/* Affichage des tuiles */

	std::function <void (const Tile &)> worldDrawTile = [MVMatrix](const Tile &t){
		// t.draw();
	};
	std::for_each(_tiles.begin(),_tiles.end(),worldDrawTile);


}
void Personnage::draw() const{
	_model.draw();
}
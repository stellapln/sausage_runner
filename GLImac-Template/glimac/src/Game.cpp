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
	
    glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
    _render->reset();

    _modelLib->perso(_currentPerso).draw();
	/*viewMatrix = cam.getMatrixView(); // Get the view Matrix from the camera

    render.reset();
    render.sendLight(viewMatrix);
    // Models
    MVMatrix = viewMatrix*MVMatrix;
    render.sendMatrix(MVMatrix);

    perso.draw();*/
        
	/* Affichage des tuiles */

	std::function <void (const Tile &)> worldDrawTile = [MVMatrix](const Tile &t){
		// t.draw();
	};
	std::for_each(_tiles.begin(),_tiles.end(),worldDrawTile);


}
void Personnage::draw() const{
	_model.draw();
}
Library::Library(Model coin):_coin(coin){}
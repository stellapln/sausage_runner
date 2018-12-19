/**
 * \file main.cpp
 * \brief Main file of Sausage Runner.
 * \author Baptiste M. Stella P. Louise P.
 * \date 17 decembre 2018
 *
 * Main program to run the game Sausage Runner.
 *
 */



#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Sphere.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glimac/Image.hpp>
#include <random>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/TrackballCamera.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glimac/Model.hpp>
#include <glimac/Game.hpp>


/*! \namespace glimac
 * 
 * Namespace with all fonctions
 * to initialise and run the game
 */
using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    //Program prog = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl", applicationPath.dirPath() + "shaders/pointLight.fs.glsl");
    Render render(applicationPath.dirPath() + "shaders/3D.vs.glsl",applicationPath.dirPath() + "shaders/directionalLight.fs.glsl");
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    /*!
     *  \brief ** Initialization
     *
     *  Initialize the game
     */

    World world("./levels/Level1");
    Model saucisse("assets/saucisse.obj");

    /*!
     *  \brief ** Loading
     *
     *  Loading objects from .obj
     */
    
    Model normalModel("assets/bloc-normal.obj");
    Model rightWholeModel("assets/trouDroite.obj");
    Model leftHoleModel("assets/trouGauche.obj");

    Model ketchupModel("assets/ketchup.obj");
    Model mustardModel("assets/moutarde.obj");
    Model preserveModel("assets/conserve.obj");
    Model juiceModel("assets/jus.obj");

    Model magnetModel("assets/aimant.obj");
    Model shieldModel("assets/bouclier.obj");

    Model coinModel("assets/piece.obj");

    Model montainSkyModel("assets/box.obj");
    
    /*!
     *  \brief ** Libraries
     *
     *  Filling libraries with objects
     */

    Library mainLib(coinModel);

    mainLib.addPerso(saucisse);

    mainLib.addSupport(normalModel);
    mainLib.addSupport(rightWholeModel);
    mainLib.addSupport(leftHoleModel);

    mainLib.addObstacle(ketchupModel);
    mainLib.addObstacle(mustardModel);
    mainLib.addObstacle(preserveModel);
    mainLib.addObstacle(juiceModel);

    mainLib.addBonus(magnetModel);
    mainLib.addBonus(shieldModel);

    mainLib.addSkybox(montainSkyModel);

    world.setLibrary(&mainLib);
    world.setRender(&render);

    /*!
     *  \brief ** Variables
     *
     *  Initializing variables for the loop
     */
    
    glm::mat4 MVMatrix;
    glm::mat4 viewMatrix;

    glEnable(GL_DEPTH_TEST);

    
    /*!
     *  \brief ** Main loop
     *
     *  Application loop for the game
     */
    
    //TTF_Init(); 
    
    bool done = false;
    int global_time = 0;
    int game_statut = 1;

    while(!done) {
    	SDL_Event e;
	    while(windowManager.pollEvent(e)) {
	        if(e.type == SDL_QUIT) {
	            done = true; //Leave the loop after this iteration
	        }
	        
	        /*!
	         *  \brief * Mouse
	         *
	         *  Mouse events
	         */
	        else if(e.type == SDL_MOUSEMOTION && edit_mode) {
                int x,y;
                SDL_GetMouseState(&x, &y);
                world.mouseMotion(x,y);
	        }
	       else if(e.type == SDL_MOUSEBUTTONDOWN) {
	            if(e.button.button == SDL_BUTTON_RIGHT) {
	                rightClickDown = true;
	                SDL_GetMouseState(&lastX, &lastY);
	            }
	            else if(e.button.button == SDL_BUTTON_WHEELUP && edit_mode){
	                cam()->moveFront(0.3);
	            }
	            else if(e.button.button == SDL_BUTTON_WHEELDOWN && edit_mode){
	                cam()->moveFront(-0.3);
	            }
	        }
	        else if(e.type == SDL_MOUSEBUTTONUP) {
	            if(e.button.button == SDL_BUTTON_RIGHT) {
	                rightClickDown = false;
	            }
	        }
	        
	        /*!
	         *  \brief * Keyboard
	         *
	         *  Keyboard events
	         */
	        else if(e.type == SDL_KEYDOWN) {
	            switch(e.key.keysym.sym) {
	                case SDLK_z: // z to jump
	                     _perso->move_jump_bend(1);
	                    break;
	                case SDLK_s: //s to bend
	                    _perso->move_jump_bend(-1);
	                    break;
	                case SDLK_q: //q to go left
	                    _perso->move_left_right(-1);
	                    break;
	                case SDLK_d: //d to go right
	                    _perso->move_left_right(1);
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
	        else if(e->type == SDL_KEYUP) {
	            switch(e->key.keysym.sym) {
	                case SDLK_z:
	                    _perso->move_jump_bend(0);
	                    break;
	                case SDLK_s:
	                    _perso->move_jump_bend(0);
	                    break;
	                case SDLK_q:
	                    _perso->move_left_right(0);
	                    break;
	                case SDLK_d:
	                    _perso->move_left_right(0);
	                    break;
	            }
	        }
	    }
        
        if(game_statut == 0)
        {
        	// Affichage du menu
        }
        else if(game_statut == 1 && !world.draw(global_time))
        {
            game_statut = 0;
        }
        else if(game_statut == 2){
            // Pause
        }
        
        global_time++;
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}

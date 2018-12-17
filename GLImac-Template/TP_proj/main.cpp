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
    Render render(applicationPath.dirPath() + "shaders/3D.vs.glsl",applicationPath.dirPath() + "shaders/pointLight.fs.glsl");
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

     World world;

     // Model cube("assets/cube.obj"); // Loading of the cube
     Model normalModel("assets/bloc-normal.obj");
     //Tile normalTile(normalModel);

     Model saucisse("assets/saucisse.obj");
     Model coinModel("assets/saucisse.obj");

     Library mainLib(coinModel);

     mainLib.addPerso(saucisse);

     world.setLibrary(&mainLib);
     world.setRender(&render);

     glm::mat4 MVMatrix;
     glm::mat4 viewMatrix;
     // Definition of the camera

     FreeflyCamera cam(glm::vec3(0.0,1.0,2.0));

    glEnable(GL_DEPTH_TEST);

    bool rightClickDown = false;
    bool edit_mode = false;
    int goFront = 0;
    int goLeft = 0;
    int lastX = 0, lastY = 0;
    int t = 0;
    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            else if(e.type == SDL_MOUSEMOTION && edit_mode) {
                if(rightClickDown){
                    int x,y;
                    SDL_GetMouseState(&x, &y);
                    cam.rotateLeft(lastX-x);
                    cam.rotateUp(lastY-y);
                    lastX = x;
                    lastY = y;
                }
            }
           else if(e.type == SDL_MOUSEBUTTONDOWN) {
                if(e.button.button == SDL_BUTTON_RIGHT) {
                    rightClickDown = true;
                    SDL_GetMouseState(&lastX, &lastY);
                }
                else if(e.button.button == SDL_BUTTON_WHEELUP && edit_mode){
                   cam.moveFront(0.3);
                }
                else if(e.button.button == SDL_BUTTON_WHEELDOWN && edit_mode){
                    cam.moveFront(-0.3);
                }
            }
            else if(e.type == SDL_MOUSEBUTTONUP) {
                if(e.button.button == SDL_BUTTON_RIGHT) {
                    rightClickDown = false;
                }
            }
            else if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_z:
                        goFront = 1;
                        break;
                    case SDLK_s:
                        goFront = -1;
                        break;
                    case SDLK_q:
                        goLeft = 1;
                        break;
                    case SDLK_d:
                        goLeft = -1;
                        break;
                    case SDLK_l:
                        if(edit_mode)
                            edit_mode = false;
                        else
                            edit_mode = true;
                        break;
                }
            }
            else if(e.type == SDL_KEYUP) {
                switch(e.key.keysym.sym) {
                    case SDLK_z:
                        goFront = 0;
                        break;
                    case SDLK_s:
                        goFront = 0;
                        break;
                    case SDLK_q:
                        goLeft = 0;
                        break;
                    case SDLK_d:
                        goLeft = 0;
                        break;
                }
            }
        }
        if(goFront != 0) cam.moveFront(goFront*0.5);
        if(goLeft != 0) cam.moveLeft(goLeft*0.5);

        world.draw();

         /*viewMatrix = cam.getMatrixView(); // Get the view Matrix from the camera

        render.reset();
        render.sendLight(viewMatrix);
        MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0)); 
        // Models
        MVMatrix = viewMatrix*MVMatrix;
        render.sendMatrix(MVMatrix);

        saucisse.draw();
       // world.draw();

        for(unsigned int i = 0; i< 10;i++)
        {
        	MVMatrix = glm::translate(MVMatrix,glm::vec3(0.0,0.0,-1.0));

        	if(i == 5) MVMatrix = glm::rotate(MVMatrix,float(M_PI/2.0f),glm::vec3(0.0f,1.0f,0.0f));

            render.sendMatrix(MVMatrix);
            normalModel.draw();
        }

        t++;
        // Update the display
        windowManager.swapBuffers();*/
    }

    return EXIT_SUCCESS;
}

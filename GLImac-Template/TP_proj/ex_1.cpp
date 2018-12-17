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
    Program prog = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl", applicationPath.dirPath() + "shaders/directionalLight.fs.glsl");
    prog.use();

    GLuint uMVPMatrix = glGetUniformLocation(prog.getGLId(),"uMVPMatrix");
    GLuint uMVMatrix = glGetUniformLocation(prog.getGLId(),"uMVMatrix");
    GLuint uNormalMatrix = glGetUniformLocation(prog.getGLId(),"uNormalMatrix");

    GLuint uKd = glGetUniformLocation(prog.getGLId(),"uKd");
    GLuint uKs = glGetUniformLocation(prog.getGLId(),"uKs");
    GLuint uShininess = glGetUniformLocation(prog.getGLId(),"uShininess");
    GLuint uLightDir_vs = glGetUniformLocation(prog.getGLId(),"uLightDir_vs");
    GLuint uLightIntensity = glGetUniformLocation(prog.getGLId(),"uLightIntensity");

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

     Sphere sphere(1,32,16);

     glm::mat4 projMatrix;
     glm::mat4 viewMatrix;
     glm::mat4 MVMatrix;
     glm::mat4 MVMatrixModified;
     glm::mat4 NormalMatrix;
     glm::mat4 GlobalMVMatrix;

     glm::vec3 Kd(0.5,0.5,0.5);
     glm::vec3 Ks(0.5,0.5,0.5);
     float Shininess = 0.5;
     glm::vec4 LightDir_vs(1.0,1.0,1.0,0.0);
     glm::vec3 LightIntensity(0.9,1.0,1.0);


    GLuint vbo; // Vertex Buffer Object
    GLuint vao; // Vertex Array Object
    const GLuint VERTEX_ATTR_POS = 0;
    const GLuint VERTEX_ATTR_NORM= 1;
    const GLuint VERTEX_ATTR_TEX_COO= 2;

     FreeflyCamera cam(glm::vec3(0.0,0.0,5.0));

    projMatrix = glm::perspective(glm::radians(70.f),8.0f/6.0f,0.1f,100.f);
    MVMatrix = glm::translate(glm::mat4(),glm::vec3(0.0,0.0,0.0f));
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    glGenBuffers(1,&vbo); // Génère le buffer et renvoi l'id sur la variable vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount()*sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(VERTEX_ATTR_POS);
    glEnableVertexAttribArray(VERTEX_ATTR_NORM);
    glEnableVertexAttribArray(VERTEX_ATTR_TEX_COO);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(VERTEX_ATTR_POS,3,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex),(const GLvoid*)(offsetof(ShapeVertex, position)));
    glVertexAttribPointer(VERTEX_ATTR_NORM,3,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex),(const GLvoid*)(offsetof(ShapeVertex, normal)));
    glVertexAttribPointer(VERTEX_ATTR_TEX_COO,2,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex),(const GLvoid*)(offsetof(ShapeVertex, texCoords)));
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glEnable(GL_DEPTH_TEST);

    glBindVertexArray(0);


    int t = 0;
    int nbLunes = 64;

    std::vector<glm::vec3> axes;
    std::vector<glm::vec3> initialPos;
    for(int i = 0;i < nbLunes;i++)
    {
    	axes.push_back(glm::sphericalRand(3.0f));
        initialPos.push_back(glm::sphericalRand(3.0f));
    }
    bool rightClickDown = false;
    int goFront = 0;
    int goLeft = 0;
    int lastX = 0, lastY = 0;
    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            else if(e.type == SDL_MOUSEMOTION) {
                if(rightClickDown)
                {
                    int x,y;
                    SDL_GetMouseState(&x, &y);
                    cam.rotateLeft(lastX-x);
                    cam.rotateUp(lastY-y);
                    lastX = x;
                    lastY = y;
                }
            }
           else if(e.type == SDL_MOUSEBUTTONDOWN) {
                if(e.button.button == SDL_BUTTON_RIGHT)
                {
                    rightClickDown = true;
                    SDL_GetMouseState(&lastX, &lastY);
                }
            }
            else if(e.type == SDL_MOUSEBUTTONUP) {
                if(e.button.button == SDL_BUTTON_RIGHT)
                {
                    rightClickDown = false;
                }
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
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
                }
            }
            else if(e.type == SDL_KEYUP)
            {
                switch(e.key.keysym.sym)
                {
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
        if(goFront != 0) cam.moveFront(goFront*0.02);
        if(goLeft != 0) cam.moveLeft(goLeft*0.02);

        viewMatrix = cam.getMatrixView();

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);
        MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0)); 
        MVMatrix = glm::rotate(viewMatrix*MVMatrix,windowManager.getTime(),glm::vec3(0.0,1.0,0.0));

        glUniformMatrix4fv(uMVPMatrix,1,GL_FALSE,glm::value_ptr(projMatrix*MVMatrix ));
        glUniformMatrix4fv(uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix,1,GL_FALSE,glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));

        glUniform3fv(uKd,1,glm::value_ptr(Kd));
        glUniform3fv(uKs,1,glm::value_ptr(Ks));
        glUniform1f(uShininess,Shininess);
        glUniform3fv(uLightDir_vs,1,glm::value_ptr(LightDir_vs*viewMatrix*glm::rotate(glm::mat4(),windowManager.getTime(),glm::vec3(0.0,1.0,0.0))));
        glUniform3fv(uLightIntensity,1,glm::value_ptr(LightIntensity));

        glDrawArrays(GL_TRIANGLES,0,sphere.getVertexCount());

        for(int i = 0;i < nbLunes;i++)
        {
            MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0.0, 0));

			MVMatrix = glm::rotate(viewMatrix*MVMatrix,windowManager.getTime(),axes.data()[i]);
			MVMatrix = glm::translate(MVMatrix,initialPos.data()[i]);
			//MVMatrix = glm::rotate(MVMatrix,windowManager.getTime(),glm::vec3(0.0f,1.0f,0.0f));
            glUniformMatrix4fv(uNormalMatrix,1,GL_FALSE,glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
			MVMatrix = glm::scale(MVMatrix,glm::vec3(0.15f,0.15f,0.15f));

            glUniformMatrix4fv(uMVPMatrix,1,GL_FALSE,glm::value_ptr(projMatrix*MVMatrix));
            glUniformMatrix4fv(uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
	       
	        glDrawArrays(GL_TRIANGLES,0,sphere.getVertexCount());
	    }
        glBindVertexArray(0);

        t++;
        // Update the display
        windowManager.swapBuffers();
    }
    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1,&vao);

    return EXIT_SUCCESS;
}

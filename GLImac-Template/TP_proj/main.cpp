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
#include <SDL/SDL_ttf.h>
#include <glimac/TrackballCamera.hpp>
#include <SDL/SDL_mixer.h>
#include <time.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glimac/Model.hpp>
#include <glimac/Game.hpp>
#include <glimac/Interfaces2D.hpp>
#include "glimac/SDLWindowManager.hpp"
#include <glimac/Except.hpp>

#define START_MENU 0
#define RUNNING_SAUSAGE 1
#define PAUSE_MENU 2
#define SCORE_MENU 3
#define QUIT_VALUE 4 


/*! \namespace glimac
 * 
 * Namespace with all fonctions
 * to initialise and run the game
 */
using namespace glimac;


/* \namespace sausageRunner
 *
 * Name space with all the functions
 * of the game
 */
namespace sausageRunner {

    /* \main
     * main function of the game
     * with loaders and render loop
     */
    int main(int argc, char** argv) {
        srand(time(NULL));

        // Initialize SDL and open a window
        //! Window manager of the SDL
        SDLWindowManager windowManager(800, 600, "Sausage Runner"); 

        // Initialize glew for OpenGL3+ support
        GLenum glewInitError = glewInit();
        if(GLEW_OK != glewInitError) {
            std::cerr << glewGetErrorString(glewInitError) << std::endl;
            return EXIT_FAILURE;
        }

        FilePath applicationPath(argv[0]); //!< File path to get the current folder of the executable
        Render* render = new Render(applicationPath.dirPath() + "shaders/3D.vs.glsl",applicationPath.dirPath() + "shaders/directionalLight.fs.glsl"); //!< Render manager for the 3D shaders
        std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    	Program program2D = loadProgram(applicationPath.dirPath() + "shaders/interfaces2D.vs.glsl",
                                    applicationPath.dirPath() + "shaders/interfaces2D.fs.glsl");
    	program2D.use(); //!< Program for the 2D renders


        GLuint sampler2D = glGetUniformLocation(program2D.getGLId(), "uTexture"); //!< Uniform value to send the 2D textures
        GLuint matrixLocation = glGetUniformLocation(program2D.getGLId(), "uModelMatrix"); //!< Uniforme value to send the matrix the location in 2D

        bool done = false; //!< Boolean to specify the End of the main loop
        int global_time = 0; //!< global number of frame from the beginning of the exection of the game
        // 0 : menu, 1 : game, 2 : pause, 3 : end (score), 4 : quit the game, 5 : change character, 6 : settings;
        int game_statut = 0; //!< Status of the game (to make a difference between 2Ds interfaces and 3D game time
        int mouse_x,mouse_y; //!< Intergers to save the postion of the mouse


        /*!
         *  \brief ** Initialization
         *
         *  Initialize the game
         */
        World world("./levels/Level1");


        /*!
         *  \brief ** Music stuff
         *
         *  
         */

        int random_music = (rand()%3)+1;
        std::string random_str = "./assets/musics/"+ std::to_string(random_music)+".mp3";
        
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
            return EXIT_FAILURE;
        }
        Mix_Music *game_music = Mix_LoadMUS(random_str.c_str());
        Mix_PlayMusic(game_music, -1);

        /*!
         *  \brief ** Initialization 
         *
         *  Initialize Windows (2D)
         */

        Image2D menuImage("assets/textures/MENU_WINDOW.png", "menuImage");
        // Play Button
        const FilePath playpathmenu = applicationPath.dirPath() + "assets/textures/PLAY_BUTTON_FOR_MENU.png";
        Image2D playImageMenu("assets/textures/PLAY_BUTTON_FOR_MENU.png", "playImageMenu");
        // Play Button Bright (hover)
        Image2D playImageHoverMenu("assets/textures/PLAY_BUTTON_FOR_MENU_BRIGHT.png", "playImageHoverMenu");
    	// Quit Button
        Image2D quitImageMenu("assets/textures/QUIT_BUTTON_FOR_MENU.png", "quitImageMenu");
    	// Quit Button Bright (hover)
        Image2D quitImageHoverMenu("assets/textures/QUIT_BUTTON_FOR_MENU_BRIGHT.png", "quitImageHoverMenu");
        // Change Button
        Image2D changeImageMenu("assets/textures/CHANGE_BUTTON_FOR_MENU.png", "changeImageMenu");
        // Change Button Bright (hover)
        Image2D changeImageHoverMenu("assets/textures/CHANGE_BUTTON_FOR_MENU_BRIGHT.png", "changeImageHoverMenu");
        // Settings Button
        Image2D settingsImageMenu("assets/textures/SETTINGS_BUTTON_FOR_MENU.png", "settingsImageMenu");
        // Settings Button Bright (hover)
        Image2D settingsImageHoverMenu("assets/textures/SETTINGS_BUTTON_FOR_MENU_BRIGHT.png", "settingsImageHoverMenu");

        // Pause Image
        Image2D pauseImage("assets/textures/PAUSE_WINDOW.png", "pauseImage");
        // Replay Button
        Image2D replayImagePause("assets/textures/REPLAY_BUTTON_FOR_PAUSE.png", "replayImagePause");
        // Replay Button Bright (hover)
        Image2D replayImageHoverPause("assets/textures/REPLAY_BUTTON_FOR_PAUSE_BRIGHT.png", "replayImageHoverPause");
        // Quit Button
        Image2D quitImagePause("assets/textures/QUIT_BUTTON_FOR_PAUSE.png", "quitImagePause");
        // Quit Button Bright (hover)
        Image2D quitImageHoverPause("assets/textures/QUIT_BUTTON_FOR_PAUSE_BRIGHT.png", "quitImageHoverPause");
        // Change Button
        Image2D menuImagePause("assets/textures/MENU_BUTTON_FOR_PAUSE.png", "menuImagePause");
        // Change Button Bright (hover)
        Image2D menuImageHoverPause("assets/textures/MENU_BUTTON_FOR_PAUSE_BRIGHT.png", "menuImageHoverPause");

        // Score Image
        Image2D scoreImage("assets/textures/SCORE_WINDOW.png", "scoreImage");
        // Quit Button
        Image2D quitImageScore("assets/textures/QUIT_BUTTON_FOR_SCORE.png", "quitImageScore");
        // Quit Button Bright (hover)
        Image2D quitImageHoverScore("assets/textures/QUIT_BUTTON_FOR_SCORE_BRIGHT.png", "quitImageHoverScore");
        // Change Button
        Image2D changeImageScore("assets/textures/CHANGE_BUTTON_FOR_SCORE.png", "changeImageScore");
        // Change Button Bright (hover)
        Image2D changeImageHoverScore("assets/textures/CHANGE_BUTTON_FOR_SCORE_BRIGHT.png", "changeImageHoverScore");
        // Menu Button
        Image2D menuImageScore("assets/textures/MENU_BUTTON_FOR_SCORE.png", "menuImageScore");
        // Menu Button Bright (hover)
        Image2D menuImageHoverScore("assets/textures/MENU_BUTTON_FOR_SCORE_BRIGHT.png", "menuImageHoverScore"); 
        // VALUE SCORE        
        Image2D valuesScore("assets/textures/numbers.png", "valueScores");

        try
        {
        	// MENU WINDOW
        	std::unique_ptr<glimac::Image> menuImagePtr = menuImage.createImage();
        	menuImage.textureInitialization(sampler2D, matrixLocation, menuImagePtr);
        	// Play button
        	std::unique_ptr<glimac::Image> playImagePtrMenu = playImageMenu.createImage();
        	playImageMenu.textureInitialization(sampler2D, matrixLocation, playImagePtrMenu);
        	// Play button bright
        	std::unique_ptr<glimac::Image> playImageHoverPtrMenu = playImageHoverMenu.createImage();
        	playImageHoverMenu.textureInitialization(sampler2D, matrixLocation, playImageHoverPtrMenu);
        	// Quit button
        	std::unique_ptr<glimac::Image> quitImagePtrMenu = quitImageMenu.createImage();
        	quitImageMenu.textureInitialization(sampler2D, matrixLocation, quitImagePtrMenu);
        	// Quit button bright
        	std::unique_ptr<glimac::Image> quitImageHoverPtrMenu = quitImageHoverMenu.createImage();
        	quitImageHoverMenu.textureInitialization(sampler2D, matrixLocation, quitImageHoverPtrMenu);
        	// Change button
        	std::unique_ptr<glimac::Image> changeImagePtrMenu = changeImageMenu.createImage();
        	changeImageMenu.textureInitialization(sampler2D, matrixLocation, changeImagePtrMenu);
            // Change button bright
            std::unique_ptr<glimac::Image> changeImageHoverPtrMenu = changeImageHoverMenu.createImage();
            changeImageHoverMenu.textureInitialization(sampler2D, matrixLocation, changeImageHoverPtrMenu);
        	// Settings button
        	std::unique_ptr<glimac::Image> settingsImagePtrMenu = settingsImageMenu.createImage();
        	settingsImageMenu.textureInitialization(sampler2D, matrixLocation, settingsImagePtrMenu);
            // Settings button bright
            std::unique_ptr<glimac::Image> settingsImageHoverPtrMenu = settingsImageHoverMenu.createImage();
            settingsImageHoverMenu.textureInitialization(sampler2D, matrixLocation, settingsImageHoverPtrMenu);


            // PAUSE WINDOW
            std::unique_ptr<glimac::Image> pauseImagePtr = pauseImage.createImage();
            pauseImage.textureInitialization(sampler2D, matrixLocation, pauseImagePtr);
            // Replay button
            std::unique_ptr<glimac::Image> replayImagePtrPause = replayImagePause.createImage();
            replayImagePause.textureInitialization(sampler2D, matrixLocation, replayImagePtrPause);
            // Replay button bright
            std::unique_ptr<glimac::Image> replayImageHoverPtrPause = replayImageHoverPause.createImage();
            replayImageHoverPause.textureInitialization(sampler2D, matrixLocation, replayImageHoverPtrPause);
            // Quit button
            std::unique_ptr<glimac::Image> quitImagePtrPause = quitImagePause.createImage();
            quitImagePause.textureInitialization(sampler2D, matrixLocation, quitImagePtrPause);
            // Quit button bright
            std::unique_ptr<glimac::Image> quitImageHoverPtrPause = quitImageHoverPause.createImage();
            quitImageHoverPause.textureInitialization(sampler2D, matrixLocation, quitImageHoverPtrPause);
            // Menu button
            std::unique_ptr<glimac::Image> menuImagePtrPause = menuImagePause.createImage();
            menuImagePause.textureInitialization(sampler2D, matrixLocation, menuImagePtrPause);
            // Menu button bright
            std::unique_ptr<glimac::Image> menuImageHoverPtrPause = menuImageHoverPause.createImage();
            menuImageHoverPause.textureInitialization(sampler2D, matrixLocation, menuImageHoverPtrPause);

            // SCORE WINDOW
            std::unique_ptr<glimac::Image> scoreImagePtr = scoreImage.createImage();
            scoreImage.textureInitialization(sampler2D, matrixLocation, scoreImagePtr);
            // Quit button
            std::unique_ptr<glimac::Image> quitImagePtrScore = quitImageScore.createImage();
            quitImageScore.textureInitialization(sampler2D, matrixLocation, quitImagePtrScore);
            // Quit button bright
            std::unique_ptr<glimac::Image> quitImageHoverPtrScore = quitImageHoverScore.createImage();
            quitImageHoverScore.textureInitialization(sampler2D, matrixLocation, quitImageHoverPtrScore);
            // Change button
            std::unique_ptr<glimac::Image> changeImagePtrScore = changeImageScore.createImage();
            changeImageScore.textureInitialization(sampler2D, matrixLocation, changeImagePtrScore);
            // Change button bright
            std::unique_ptr<glimac::Image> changeImageHoverPtrScore = changeImageHoverScore.createImage();
            changeImageHoverScore.textureInitialization(sampler2D, matrixLocation, changeImageHoverPtrScore);
            // Menu button
            std::unique_ptr<glimac::Image> menuImagePtrScore = menuImageScore.createImage();
            menuImageScore.textureInitialization(sampler2D, matrixLocation, menuImagePtrScore);
            // Menu button bright
            std::unique_ptr<glimac::Image> menuImageHoverPtrScore = menuImageHoverScore.createImage();
            menuImageHoverScore.textureInitialization(sampler2D, matrixLocation, menuImageHoverPtrScore);

            // Score
            std::unique_ptr<glimac::Image> scoreNumberImagePtr = valuesScore.createImage();


        }
        catch (Except err)
        {
        	std::cerr << err.what() << std::endl;
        }
        
        // MENU WINDOW
        Window menu(&menuImage);
        Button play_menu(&playImageMenu, &playImageHoverMenu,[&world, &global_time]()-> int{
                    world.init(global_time);
    				return 1; // start the game

    			},152,427,217/2,348/2);
        Button quit_menu(&quitImageMenu, &quitImageHoverMenu,[]()-> int {
    				return 4; // quit the game
    			},20,440,93,165);
        Button change_menu(&changeImageMenu, &changeImageHoverMenu,[]()-> int{
    				return 5; // go to change character
    			},557,445,218,155);
        Button settings_menu(&settingsImageMenu, &settingsImageHoverMenu,[]()-> int{
    				return 6; // go to settings
    			},440,470,139*0.75,156*0.75);

        // PAUSE WINDOW
        Window pause(&pauseImage);
        Button replay_pause(&replayImagePause, &replayImageHoverPause,[&world]()-> int{
                    world.resume();
                    return 1; // replay the game
                    // back to play + reset world
                },499,426,140,173);
        Button quit_pause(&quitImagePause, &quitImageHoverPause,[]()-> int{
                    return 4; // quit the game
                },390,432,96,169);
        Button menu_pause(&menuImagePause, &menuImageHoverPause,[]()-> int{
                    return 0; // go to menu
                },648,399,115,201);

        // SCORE WINDOW
        Window score(&scoreImage);
        Button quit_score(&quitImageScore, &quitImageHoverScore,[]()-> int{
                    return 4; // quit the game
                },372,464,77,136);
        Button menu_score(&menuImageScore, &menuImageHoverScore,[]()-> int{
                    return 0; // go to the menu
                },657,417,106,184);
        Button change_score(&changeImageScore, &changeImageHoverScore,[]()-> int{
                    return 5; // change character
                },454,460,193,140);

        //render->addLight(new Light(glm::vec3(1.0,1.0,3.0),glm::vec3(30.0,0.0,0.0),1));
        //render->addLight(new Light(glm::vec3(0.0,1.0,-5.0),glm::vec3(20.0,20.0,20.0),1));
        //render->addLight(new Light(glm::vec3(0.0,0.0,-10.0),glm::vec3(20.0,20.0,20.0),1));


    	try
        {
        	menu.addButton(play_menu);
        	menu.addButton(quit_menu);
        	menu.addButton(change_menu);
        	menu.addButton(settings_menu);

            pause.addButton(replay_pause);
            pause.addButton(quit_pause);
            pause.addButton(menu_pause);

            score.addButton(quit_score);
            score.addButton(menu_score);
            score.addButton(change_score);
        }
        catch (Except err)
        {
        	std::cerr << err.what() << std::endl;
        }

        /*!
         *  \brief ** Loading
         *
         *  Loading objects from .obj
         */

        Model saucisse("assets/saucisse.obj");
        
        Model normalModel("assets/bloc-normal.obj");
        Model rightWholeModel("assets/trouDroite.obj");
        Model leftHoleModel("assets/trouGauche.obj");

        Model ketchupModel("assets/ketchup.obj");
        Model mustardModel("assets/moutarde.obj");
        Model preserveModel("assets/conserve.obj");
        Model juiceModel("assets/jus.obj");

        Model magnetModel("assets/aimant.obj");
        Model shieldModel("assets/bouclier.obj");
        Model bonusX2Model("assets/bonusX2.obj");

        Model coinModel("assets/piece.obj");

        Model protectModel("assets/bloc-bleu.obj");
        Model poireModel("assets/PoireDeLavement.obj");
        Model donutModel("assets/donut.obj");

        Model montainSkyModel("assets/skydome.obj");
        /*!
         *  \brief ** Libraries
         *
         *  Filling libraries with objects
         */

        Library *mainLib = new Library(coinModel);

        mainLib->addPerso(saucisse);

        mainLib->addSupport(normalModel);
        mainLib->addSupport(rightWholeModel);
        mainLib->addSupport(leftHoleModel);

        mainLib->addObstacle(ketchupModel);
        mainLib->addObstacle(mustardModel);
        mainLib->addObstacle(preserveModel);
        mainLib->addObstacle(juiceModel);

        mainLib->addBonus(magnetModel);
        mainLib->addBonus(shieldModel);
        mainLib->addBonus(bonusX2Model);

        mainLib->addSkybox(montainSkyModel);

        mainLib->addSpecial(protectModel);
        mainLib->addSpecial(poireModel);
        mainLib->addSpecial(donutModel);

        /*!
         *  \brief ** Score stuff
         *
         *  Score call & draw
         *
        

        Score points();
        SDL_Rect position;
        Text::initText();
        */


        //! Set the library use in the world
        world.setLibrary(mainLib);
        //! Set the render manager of the world
        world.setRender(render);

    	//glEnable(GL_DEPTH_TEST);

        /*!
         *  \brief ** Main loop
         *
         *  Application loop for the game
         */

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
    	        else if(e.type == SDL_MOUSEMOTION) {
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    if(game_statut == RUNNING_SAUSAGE)
                    {
                    	world.mouseMotion(mouse_x,mouse_y);
                    }
    	        }
    	       else if(e.type == SDL_MOUSEBUTTONDOWN) {
    	       		if(game_statut == START_MENU)
    	       		{
                    	Button* bmenu = menu.activeButton(mouse_x,mouse_y);
                    	if(bmenu != nullptr){
                			game_statut = bmenu->action()();
                		}
    	       		}
    	       		else if(game_statut == RUNNING_SAUSAGE)
    	       		{
    	           		world.mouseButtonDown(e.button.button);	
    	       		}
    	       		else if(game_statut == PAUSE_MENU)
    	       		{
                    	Button* bpause = pause.activeButton(mouse_x,mouse_y);
                    	if(bpause != nullptr){
    	                    game_statut = bpause->action()();
    	                }
    	       		}
    	       		else if(game_statut == SCORE_MENU)
    	       		{
                		Button* bscore = score.activeButton(mouse_x,mouse_y);
                		if(bscore != nullptr){
    	                    game_statut = bscore->action()();
    	                }
    	       		}
    	        }
    	        else if(e.type == SDL_MOUSEBUTTONUP) {
    	            world.mouseButtonUp(e.button.button);
    	        }
    	        
    	        /*!
    	         *  \brief * Keyboard
    	         *
    	         *  Keyboard events
    	         */
    	        else if(e.type == SDL_KEYDOWN) {
    	        	world.keyDown(e.key.keysym.sym, global_time);
    	        }
    	        else if(e.type == SDL_KEYUP) {
                   if((e.key.keysym.sym == SDLK_p || e.key.keysym.sym == SDLK_ESCAPE) && game_statut == RUNNING_SAUSAGE)
                   {
                        game_statut = PAUSE_MENU;
                        program2D.use();
                        world.close();

                   }
    	           else world.keyUp(e.key.keysym.sym, global_time);
    	        }
    	    }
            
            if(game_statut == START_MENU)
            {
            	Button* bmenu = menu.activeButton(mouse_x,mouse_y);
    			if(bmenu != nullptr){
    	            bmenu->Is_Hover(true);
    	        }

            	// draw menu window
            	menu.drawWindow();
            }
            else if(game_statut == RUNNING_SAUSAGE)
            {
                game_statut = world.draw(global_time);
                if(game_statut != RUNNING_SAUSAGE) 
                {
                    world.close();
                    program2D.use();
                }
            }
            else if(game_statut == PAUSE_MENU){
            	Button* bpause = pause.activeButton(mouse_x,mouse_y);
    	        if(bpause != nullptr){
    	            bpause->Is_Hover(true);
    	        }
    	        // draw pause window
    	        pause.drawWindow();
            }
            else if(game_statut == SCORE_MENU){
            	Button* bscore = score.activeButton(mouse_x,mouse_y);
    			if(bscore != nullptr){
    	            bscore->Is_Hover(true);
    	        }
    	        // draw score window
    	        score.drawWindow();

                int currentScore = world.getScore();
                world.saveScore();
            }
            else if(game_statut == QUIT_VALUE){
                done = true;
            }

            else{
                game_statut = START_MENU;
            }

            global_time++;
            windowManager.swapBuffers();


               
        }
        return EXIT_SUCCESS;
    }
}

int main(int argc, char** argv){
    return sausageRunner::main(argc,argv);
}

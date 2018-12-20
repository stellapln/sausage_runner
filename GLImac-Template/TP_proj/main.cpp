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
#include <glimac/Interfaces2D.hpp>
#include <glimac/Except.hpp>

/*! \namespace glimac
 * 
 * Namespace with all fonctions
 * to initialise and run the game
 */
using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "Sausage Runner");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }
std::cout << "1" << std::endl;

    FilePath applicationPath(argv[0]);
    Render* render = new Render(applicationPath.dirPath() + "shaders/3D.vs.glsl",applicationPath.dirPath() + "shaders/directionalLight.fs.glsl");
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	Program program2D = loadProgram(applicationPath.dirPath() + "shaders/interfaces2D.vs.glsl",
                                applicationPath.dirPath() + "shaders/interfaces2D.fs.glsl");
	program2D.use();


    GLuint sampler2D = glGetUniformLocation(program2D.getGLId(), "uTexture");
    GLuint matrixLocation = glGetUniformLocation(program2D.getGLId(), "uModelMatrix");

    bool done = false;
    int global_time = 0;
    // 0 : menu, 1 : game, 2 : pause, 3 : end (score), 4 : quit the game, 5 : change character, 6 : settings;
    int game_statut = 0;
    int mouse_x,mouse_y;

std::cout << "2" << std::endl;

    /*!
     *  \brief ** Initialization
     *
     *  Initialize the game
     */

    World world("./levels/Level1");

    /*!
     *  \brief ** Initialization 
     *
     *  Initialize Windows (2D)
     */

     // Menu Image
    const FilePath menupath = applicationPath.dirPath() + "assets/textures/MENU_WINDOW.png";
    Image2D menuImage(menupath, "menuImage");
    // Play Button
    const FilePath playpathmenu = applicationPath.dirPath() + "assets/textures/PLAY_BUTTON_FOR_MENU.png";
    Image2D playImageMenu(playpathmenu, "playImageMenu");
    // Play Button Bright (hover)
    const FilePath playpathhovermenu = applicationPath.dirPath() + "assets/textures/PLAY_BUTTON_FOR_MENU_BRIGHT.png";
    Image2D playImageHoverMenu(playpathhovermenu, "playImageHoverMenu");
	// Quit Button
    const FilePath quitpathmenu = applicationPath.dirPath() + "assets/textures/QUIT_BUTTON_FOR_MENU.png";
    Image2D quitImageMenu(quitpathmenu, "quitImageMenu");
	// Quit Button Bright (hover)
    const FilePath quitpathhovermenu = applicationPath.dirPath() + "assets/textures/QUIT_BUTTON_FOR_MENU_BRIGHT.png";
    Image2D quitImageHoverMenu(quitpathhovermenu, "quitImageHoverMenu");
    // Change Button
    const FilePath changepathmenu = applicationPath.dirPath() + "assets/textures/CHANGE_BUTTON_FOR_MENU.png";
    Image2D changeImageMenu(changepathmenu, "changeImageMenu");
    // Change Button Bright (hover)
    const FilePath changepathhovermenu = applicationPath.dirPath() + "assets/textures/CHANGE_BUTTON_FOR_MENU_BRIGHT.png";
    Image2D changeImageHoverMenu(changepathhovermenu, "changeImageHoverMenu");
    // Settings Button
    const FilePath settingspathmenu = applicationPath.dirPath() + "assets/textures/SETTINGS_BUTTON_FOR_MENU.png";
    Image2D settingsImageMenu(settingspathmenu, "settingsImageMenu");
    // Settings Button Bright (hover)
    const FilePath settingspathhovermenu = applicationPath.dirPath() + "assets/textures/SETTINGS_BUTTON_FOR_MENU_BRIGHT.png";
    Image2D settingsImageHoverMenu(settingspathhovermenu, "settingsImageHoverMenu");

    // Pause Image
    const FilePath pausepath = applicationPath.dirPath() + "assets/textures/PAUSE_WINDOW.png";
    Image2D pauseImage(pausepath, "pauseImage");
    // Replay Button
    const FilePath replaypathpause = applicationPath.dirPath() + "assets/textures/REPLAY_BUTTON_FOR_PAUSE.png";
    Image2D replayImagePause(replaypathpause, "replayImagePause");
    // Replay Button Bright (hover)
    const FilePath replaypathhoverpause = applicationPath.dirPath() + "assets/textures/REPLAY_BUTTON_FOR_PAUSE_BRIGHT.png";
    Image2D replayImageHoverPause(replaypathhoverpause, "replayImageHoverPause");
    // Quit Button
    const FilePath quitpathpause = applicationPath.dirPath() + "assets/textures/QUIT_BUTTON_FOR_PAUSE.png";
    Image2D quitImagePause(quitpathpause, "quitImagePause");
    // Quit Button Bright (hover)
    const FilePath quitpathhoverpause = applicationPath.dirPath() + "assets/textures/QUIT_BUTTON_FOR_PAUSE_BRIGHT.png";
    Image2D quitImageHoverPause(quitpathhoverpause, "quitImageHoverPause");
    // Change Button
    const FilePath menupathpause = applicationPath.dirPath() + "assets/textures/MENU_BUTTON_FOR_PAUSE.png";
    Image2D menuImagePause(menupathpause, "menuImagePause");
    // Change Button Bright (hover)
    const FilePath menupathhoverpause = applicationPath.dirPath() + "assets/textures/MENU_BUTTON_FOR_PAUSE_BRIGHT.png";
    Image2D menuImageHoverPause(menupathhoverpause, "menuImageHoverPause");

    // Score Image
    const FilePath scorepath = applicationPath.dirPath() + "assets/textures/SCORE_WINDOW.png";
    Image2D scoreImage(scorepath, "scoreImage");
    // Quit Button
    const FilePath quitpathscore = applicationPath.dirPath() + "assets/textures/QUIT_BUTTON_FOR_SCORE.png";
    Image2D quitImageScore(quitpathscore, "quitImageScore");
    // Quit Button Bright (hover)
    const FilePath quitpathhoverscore = applicationPath.dirPath() + "assets/textures/QUIT_BUTTON_FOR_SCORE_BRIGHT.png";
    Image2D quitImageHoverScore(quitpathhoverscore, "quitImageHoverScore");
    // Change Button
    const FilePath changepathscore = applicationPath.dirPath() + "assets/textures/CHANGE_BUTTON_FOR_SCORE.png";
    Image2D changeImageScore(changepathscore, "changeImageScore");
    // Change Button Bright (hover)
    const FilePath changepathhoverscore = applicationPath.dirPath() + "assets/textures/CHANGE_BUTTON_FOR_SCORE_BRIGHT.png";
    Image2D changeImageHoverScore(changepathhoverscore, "changeImageHoverScore");
    // Menu Button
    const FilePath menupathscore = applicationPath.dirPath() + "assets/textures/MENU_BUTTON_FOR_SCORE.png";
    Image2D menuImageScore(menupathscore, "menuImageScore");
    // Menu Button Bright (hover)
    const FilePath menupathhoverscore = applicationPath.dirPath() + "assets/textures/MENU_BUTTON_FOR_SCORE_BRIGHT.png";
    Image2D menuImageHoverScore(menupathhoverscore, "menuImageHoverScore");

std::cout << "3" << std::endl;
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

    }
    catch (std::string err)
    {
    	std::cerr << err << std::endl;
    }
std::cout << "4" << std::endl;
    
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

std::cout << "5" << std::endl;

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
    catch (std::string err)
    {
    	std::cerr << err << std::endl;
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

    Model montainSkyModel("assets/skydome.obj");
    
    /*!
     *  \brief ** Libraries
     *
     *  Filling libraries with objects
     */
std::cout << "6" << std::endl;

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

    world.setLibrary(mainLib);
    world.setRender(render);

	//glEnable(GL_DEPTH_TEST);

    /*!
     *  \brief ** Main loop
     *
     *  Application loop for the game
     */
    
    // TTF_Init(); 
std::cout << "7" << std::endl;

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
                if(game_statut == 1)
                {
                	world.mouseMotion(mouse_x,mouse_y);
                }
	        }
	       else if(e.type == SDL_MOUSEBUTTONDOWN) {
	       		if(game_statut == 0)
	       		{
                	Button* bmenu = menu.activeButton(mouse_x,mouse_y);
                	if(bmenu != nullptr){
            			game_statut = bmenu->action()();
            		}
	       		}
	       		else if(game_statut == 1)
	       		{
	           		world.mouseButtonDown(e.button.button);	
	       		}
	       		else if(game_statut == 2)
	       		{
                	Button* bpause = pause.activeButton(mouse_x,mouse_y);
                	if(bpause != nullptr){
	                    game_statut = bpause->action()();
	                }
	       		}
	       		else if(game_statut == 3)
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
               if(e.key.keysym.sym == SDLK_ESCAPE) done = true;
               else if(e.key.keysym.sym == SDLK_p && game_statut == 1)
               {
                    game_statut = 2;
                    program2D.use();
                    world.close();

               }
	           else world.keyUp(e.key.keysym.sym, global_time);
	        }
	    }
        
        if(game_statut == 0)
        {
        	Button* bmenu = menu.activeButton(mouse_x,mouse_y);
			if(bmenu != nullptr){
	            bmenu->Is_Hover(true);
	        }
        	// draw menu window
        	menu.drawWindow();
        }
        else if(game_statut == 1)
        {
            game_statut = world.draw(global_time);
            if(game_statut != 1)
            {
                world.close();
                program2D.use();
            }
        }
        else if(game_statut == 2){
        	Button* bpause = pause.activeButton(mouse_x,mouse_y);
	        if(bpause != nullptr){
	            bpause->Is_Hover(true);
	        }
	        // draw pause window
	        pause.drawWindow();
        }
        else if(game_statut == 3){
        	Button* bscore = score.activeButton(mouse_x,mouse_y);
			if(bscore != nullptr){
	            bscore->Is_Hover(true);
	        }
	        // draw score window
	        score.drawWindow();
        }
        else if(game_statut == 4){
            done = true;
        }
        
        global_time++;
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}

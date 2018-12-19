// #include "glimac/Interfaces2D.hpp"


// int main(int argc, char** argv) {
//     // Initialize SDL and open a window
//     SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Sausage Runner");

//     // Initialize glew for OpenGL3+ support
//     GLenum glewInitError = glewInit();
//     if(GLEW_OK != glewInitError) {
//         std::cerr << glewGetErrorString(glewInitError) << std::endl;
//         return EXIT_FAILURE;
//     }

//     std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
//     std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

//     FilePath applicationPath(argv[0]);

//     Program program;

//     if(argc != 3) {
//         // load and compile shaders
//         program = loadProgram(applicationPath.dirPath() + "shaders/interfaces2D.vs.glsl",
//                                     applicationPath.dirPath() + "shaders/interfaces2D.fs.glsl");
//         program.use();
//     }
//     else{
//         // load and compile shaders in argu
//         program = loadProgram(applicationPath.dirPath() + "shaders/" + argv[1],
//                                      applicationPath.dirPath() + "shaders/" +argv[2]);
//         program.use();
//     }

//     GLuint sampler2D = glGetUniformLocation(program.getGLId(), "uTexture");
//     GLuint matrixLocation = glGetUniformLocation(program.getGLId(), "uModelMatrix");

//     // Menu Image
//     const FilePath menupath = applicationPath.dirPath() + "assets/textures/MENU_WINDOW.png";
//     Image2D menuImage(menupath, "menuImage");
//     // Play Button
//     const FilePath playpathmenu = applicationPath.dirPath() + "assets/textures/PLAY_BUTTON_FOR_MENU.png";
//     Image2D playImageMenu(playpathmenu, "playImageMenu");
//     // Play Button Bright (hover)
//     const FilePath playpathhovermenu = applicationPath.dirPath() + "assets/textures/PLAY_BUTTON_FOR_MENU_BRIGHT.png";
//     Image2D playImageHoverMenu(playpathhovermenu, "playImageHoverMenu");
// 	// Quit Button
//     const FilePath quitpathmenu = applicationPath.dirPath() + "assets/textures/QUIT_BUTTON_FOR_MENU.png";
//     Image2D quitImageMenu(quitpathmenu, "quitImageMenu");
// 	// Quit Button Bright (hover)
//     const FilePath quitpathhovermenu = applicationPath.dirPath() + "assets/textures/QUIT_BUTTON_FOR_MENU_BRIGHT.png";
//     Image2D quitImageHoverMenu(quitpathhovermenu, "quitImageHoverMenu");
//     // Change Button
//     const FilePath changepathmenu = applicationPath.dirPath() + "assets/textures/CHANGE_BUTTON_FOR_MENU.png";
//     Image2D changeImageMenu(changepathmenu, "changeImageMenu");
//     // Change Button Bright (hover)
//     const FilePath changepathhovermenu = applicationPath.dirPath() + "assets/textures/CHANGE_BUTTON_FOR_MENU_BRIGHT.png";
//     Image2D changeImageHoverMenu(changepathhovermenu, "changeImageHoverMenu");
//     // Settings Button
//     const FilePath settingspathmenu = applicationPath.dirPath() + "assets/textures/SETTINGS_BUTTON_FOR_MENU.png";
//     Image2D settingsImageMenu(settingspathmenu, "settingsImageMenu");
//     // Settings Button Bright (hover)
//     const FilePath settingspathhovermenu = applicationPath.dirPath() + "assets/textures/SETTINGS_BUTTON_FOR_MENU_BRIGHT.png";
//     Image2D settingsImageHoverMenu(settingspathhovermenu, "settingsImageHoverMenu");

//     // Pause Image
//     const FilePath pausepath = applicationPath.dirPath() + "assets/textures/PAUSE_WINDOW.png";
//     Image2D pauseImage(pausepath, "pauseImage");
//     // Replay Button
//     const FilePath replaypathpause = applicationPath.dirPath() + "assets/textures/REPLAY_BUTTON_FOR_PAUSE.png";
//     Image2D replayImagePause(replaypathpause, "replayImagePause");
//     // Replay Button Bright (hover)
//     const FilePath replaypathhoverpause = applicationPath.dirPath() + "assets/textures/REPLAY_BUTTON_FOR_PAUSE_BRIGHT.png";
//     Image2D replayImageHoverPause(replaypathhoverpause, "replayImageHoverPause");
//     // Quit Button
//     const FilePath quitpathpause = applicationPath.dirPath() + "assets/textures/QUIT_BUTTON_FOR_PAUSE.png";
//     Image2D quitImagePause(quitpathpause, "quitImagePause");
//     // Quit Button Bright (hover)
//     const FilePath quitpathhoverpause = applicationPath.dirPath() + "assets/textures/QUIT_BUTTON_FOR_PAUSE_BRIGHT.png";
//     Image2D quitImageHoverPause(quitpathhoverpause, "quitImageHoverPause");
//     // Change Button
//     const FilePath menupathpause = applicationPath.dirPath() + "assets/textures/MENU_BUTTON_FOR_PAUSE.png";
//     Image2D menuImagePause(menupathpause, "menuImagePause");
//     // Change Button Bright (hover)
//     const FilePath menupathhoverpause = applicationPath.dirPath() + "assets/textures/MENU_BUTTON_FOR_PAUSE_BRIGHT.png";
//     Image2D menuImageHoverPause(menupathhoverpause, "menuImageHoverPause");

//     // Score Image
//     const FilePath scorepath = applicationPath.dirPath() + "assets/textures/SCORE_WINDOW.png";
//     Image2D scoreImage(scorepath, "scoreImage");
//     // Quit Button
//     const FilePath quitpathscore = applicationPath.dirPath() + "assets/textures/QUIT_BUTTON_FOR_SCORE.png";
//     Image2D quitImageScore(quitpathscore, "quitImageScore");
//     // Quit Button Bright (hover)
//     const FilePath quitpathhoverscore = applicationPath.dirPath() + "assets/textures/QUIT_BUTTON_FOR_SCORE_BRIGHT.png";
//     Image2D quitImageHoverScore(quitpathhoverscore, "quitImageHoverScore");
//     // Change Button
//     const FilePath changepathscore = applicationPath.dirPath() + "assets/textures/CHANGE_BUTTON_FOR_SCORE.png";
//     Image2D changeImageScore(changepathscore, "changeImageScore");
//     // Change Button Bright (hover)
//     const FilePath changepathhoverscore = applicationPath.dirPath() + "assets/textures/CHANGE_BUTTON_FOR_SCORE_BRIGHT.png";
//     Image2D changeImageHoverScore(changepathhoverscore, "changeImageHoverScore");
//     // Menu Button
//     const FilePath menupathscore = applicationPath.dirPath() + "assets/textures/MENU_BUTTON_FOR_SCORE.png";
//     Image2D menuImageScore(menupathscore, "menuImageScore");
//     // Menu Button Bright (hover)
//     const FilePath menupathhoverscore = applicationPath.dirPath() + "assets/textures/MENU_BUTTON_FOR_SCORE_BRIGHT.png";
//     Image2D menuImageHoverScore(menupathhoverscore, "menuImageHoverScore");

//     try
//     {
//     	// MENU WINDOW
//     	std::unique_ptr<glimac::Image> menuImagePtr = menuImage.createImage();
//     	menuImage.textureInitialization(sampler2D, matrixLocation, menuImagePtr);
//     	// Play button
//     	std::unique_ptr<glimac::Image> playImagePtrMenu = playImageMenu.createImage();
//     	playImageMenu.textureInitialization(sampler2D, matrixLocation, playImagePtrMenu);
//     	// Play button bright
//     	std::unique_ptr<glimac::Image> playImageHoverPtrMenu = playImageHoverMenu.createImage();
//     	playImageHoverMenu.textureInitialization(sampler2D, matrixLocation, playImageHoverPtrMenu);
//     	// Quit button
//     	std::unique_ptr<glimac::Image> quitImagePtrMenu = quitImageMenu.createImage();
//     	quitImageMenu.textureInitialization(sampler2D, matrixLocation, quitImagePtrMenu);
//     	// Quit button bright
//     	std::unique_ptr<glimac::Image> quitImageHoverPtrMenu = quitImageHoverMenu.createImage();
//     	quitImageHoverMenu.textureInitialization(sampler2D, matrixLocation, quitImageHoverPtrMenu);
//     	// Change button
//     	std::unique_ptr<glimac::Image> changeImagePtrMenu = changeImageMenu.createImage();
//     	changeImageMenu.textureInitialization(sampler2D, matrixLocation, changeImagePtrMenu);
//         // Change button bright
//         std::unique_ptr<glimac::Image> changeImageHoverPtrMenu = changeImageHoverMenu.createImage();
//         changeImageHoverMenu.textureInitialization(sampler2D, matrixLocation, changeImageHoverPtrMenu);
//     	// Settings button
//     	std::unique_ptr<glimac::Image> settingsImagePtrMenu = settingsImageMenu.createImage();
//     	settingsImageMenu.textureInitialization(sampler2D, matrixLocation, settingsImagePtrMenu);
//         // Settings button bright
//         std::unique_ptr<glimac::Image> settingsImageHoverPtrMenu = settingsImageHoverMenu.createImage();
//         settingsImageHoverMenu.textureInitialization(sampler2D, matrixLocation, settingsImageHoverPtrMenu);


//         // PAUSE WINDOW
//         std::unique_ptr<glimac::Image> pauseImagePtr = pauseImage.createImage();
//         pauseImage.textureInitialization(sampler2D, matrixLocation, pauseImagePtr);
//         // Replay button
//         std::unique_ptr<glimac::Image> replayImagePtrPause = replayImagePause.createImage();
//         replayImagePause.textureInitialization(sampler2D, matrixLocation, replayImagePtrPause);
//         // Replay button bright
//         std::unique_ptr<glimac::Image> replayImageHoverPtrPause = replayImageHoverPause.createImage();
//         replayImageHoverPause.textureInitialization(sampler2D, matrixLocation, replayImageHoverPtrPause);
//         // Quit button
//         std::unique_ptr<glimac::Image> quitImagePtrPause = quitImagePause.createImage();
//         quitImagePause.textureInitialization(sampler2D, matrixLocation, quitImagePtrPause);
//         // Quit button bright
//         std::unique_ptr<glimac::Image> quitImageHoverPtrPause = quitImageHoverPause.createImage();
//         quitImageHoverPause.textureInitialization(sampler2D, matrixLocation, quitImageHoverPtrPause);
//         // Menu button
//         std::unique_ptr<glimac::Image> menuImagePtrPause = menuImagePause.createImage();
//         menuImagePause.textureInitialization(sampler2D, matrixLocation, menuImagePtrPause);
//         // Menu button bright
//         std::unique_ptr<glimac::Image> menuImageHoverPtrPause = menuImageHoverPause.createImage();
//         menuImageHoverPause.textureInitialization(sampler2D, matrixLocation, menuImageHoverPtrPause);

//         // SCORE WINDOW
//         std::unique_ptr<glimac::Image> scoreImagePtr = scoreImage.createImage();
//         scoreImage.textureInitialization(sampler2D, matrixLocation, scoreImagePtr);
//         // Quit button
//         std::unique_ptr<glimac::Image> quitImagePtrScore = quitImageScore.createImage();
//         quitImageScore.textureInitialization(sampler2D, matrixLocation, quitImagePtrScore);
//         // Quit button bright
//         std::unique_ptr<glimac::Image> quitImageHoverPtrScore = quitImageHoverScore.createImage();
//         quitImageHoverScore.textureInitialization(sampler2D, matrixLocation, quitImageHoverPtrScore);
//         // Change button
//         std::unique_ptr<glimac::Image> changeImagePtrScore = changeImageScore.createImage();
//         changeImageScore.textureInitialization(sampler2D, matrixLocation, changeImagePtrScore);
//         // Change button bright
//         std::unique_ptr<glimac::Image> changeImageHoverPtrScore = changeImageHoverScore.createImage();
//         changeImageHoverScore.textureInitialization(sampler2D, matrixLocation, changeImageHoverPtrScore);
//         // Menu button
//         std::unique_ptr<glimac::Image> menuImagePtrScore = menuImageScore.createImage();
//         menuImageScore.textureInitialization(sampler2D, matrixLocation, menuImagePtrScore);
//         // Menu button bright
//         std::unique_ptr<glimac::Image> menuImageHoverPtrScore = menuImageHoverScore.createImage();
//         menuImageHoverScore.textureInitialization(sampler2D, matrixLocation, menuImageHoverPtrScore);

//     }
//     catch (std::string err)
//     {
//     	std::cerr << err << std::endl;
//     }
    
//     // MENU WINDOW
//     Window menu(&menuImage);
//     Button play_menu(&playImageMenu, &playImageHoverMenu,[]()->int{
// 				std::cout <<  "Play Menu" << std::endl;
// 			},152,427,217/2,348/2);
//     Button quit_menu(&quitImageMenu, &quitImageHoverMenu,[]() ->int{
// 				std::cout <<  "Quit Menu" << std::endl;
// 			},20,440,93,165);
//     Button change_menu(&changeImageMenu, &changeImageHoverMenu,[]() ->int{
// 				std::cout <<  "Change Menu" << std::endl;
// 			},557,445,218,155);
//     Button settings_menu(&settingsImageMenu, &settingsImageHoverMenu, []()->int {
// 				std::cout <<  "Settings Menu" << std::endl;
// 			},440,470,139*0.75,156*0.75);

//     // PAUSE WINDOW
//     Window pause(&pauseImage);
//     Button replay_pause(&replayImagePause, &replayImageHoverPause,[]() ->int{
//                 std::cout <<  "Replay Pause" << std::endl;
//             },499,426,140,173);
//     Button quit_pause(&quitImagePause, &quitImageHoverPause,[]() ->int{
//                 std::cout <<  "Quit Pause" << std::endl;
//             },390,432,96,169);
//     Button menu_pause(&menuImagePause, &menuImageHoverPause,[]() ->int{
//                 std::cout <<  "Change Pause" << std::endl;
//             },648,399,115,201);

//     // SCORE WINDOW
//     Window score(&scoreImage);
//     Button quit_score(&quitImageScore, &quitImageHoverScore,[]()->int {
//                 std::cout <<  "Quit Score" << std::endl;
//             },372,464,77,136);
//     Button menu_score(&menuImageScore, &menuImageHoverScore,[]() ->int{
//                 std::cout <<  "Menu Score" << std::endl;
//             },657,417,106,184);
//     Button change_score(&changeImageScore, &changeImageHoverScore,[]()->int {
//                 std::cout <<  "Change Score" << std::endl;
//             },454,460,193,140);


//     try
//     {
//     	// menu.addButton(play_menu);
//     	// menu.addButton(quit_menu);
//     	// menu.addButton(change_menu);
//     	// menu.addButton(settings_menu);

//      //    pause.addButton(replay_pause);
//      //    pause.addButton(quit_pause);
//      //    pause.addButton(menu_pause);

//         score.addButton(quit_score);
//         score.addButton(menu_score);
//         score.addButton(change_score);
//     }
//     catch (std::string err)
//     {
//     	std::cerr << err << std::endl;
//     }

//     int mouse_x, mouse_y; // mouse position

//     // Application loop:
//     bool done = false;
//     while(!done) {
//         // Event loop:
//         SDL_Event e;
//         while(windowManager.pollEvent(e)) {
//             if(e.type == SDL_QUIT) {
//                 done = true; // Leave the loop after this iteration
//             }
//             else if(e.type == SDL_MOUSEMOTION)
//             {
//             	SDL_GetMouseState(&mouse_x, &mouse_y);
//             }
//             else if(e.type == SDL_MOUSEBUTTONDOWN)
//             {
//                 Button* bmenu = menu.activeButton(mouse_x,mouse_y);
//                 Button* bpause = pause.activeButton(mouse_x,mouse_y);
//             	Button* bscore = score.activeButton(mouse_x,mouse_y);
//             	if(bmenu != nullptr){
//             		bmenu->action()();
//             	}
//                 else if(bpause != nullptr){
//                     bpause->action()();
//                 }
//                 else if(bscore != nullptr){
//                     bscore->action()();
//                 }
//             }

//         }
//         Button* bmenu = menu.activeButton(mouse_x,mouse_y);
//         Button* bpause = pause.activeButton(mouse_x,mouse_y);
//         Button* bscore = score.activeButton(mouse_x,mouse_y);
//         if(bmenu != nullptr){
//             bmenu->Is_Hover(true);
//         }
//         else if(bpause != nullptr){
//             bpause->Is_Hover(true);
//         }
//         else if(bscore != nullptr){
//             bscore->Is_Hover(true);
//         }

//         // Cleaning window
//         glClear(GL_COLOR_BUFFER_BIT);

//         // draw menu window
//         // menu.drawWindow();

//         // draw pause window
//         // pause.drawWindow();

//         // draw score window
//         // score.drawWindow();


//         // Update the display
//         windowManager.swapBuffers();
//     }

//     return EXIT_SUCCESS;
// }

// Copyright 2018 Anas Idiab, Sebastian Winding.
/**
   @file main.cpp
   @author Anas Idiab and Sebastian Winding
   @date 19. Apr 2018
 */
// Includes
// This source file contains the main entry point of the application, which is
//  the main function.
#include "globals.hpp"
#include "input.hpp"
#include "scenes/mainmenu.hpp"
#include "scenes/music.hpp"
#include "scenes/stats.hpp"

/* TODO:
  - Shader interface
  - point/gameobject intersection function
  - mouseover support
*/

/** Main application entry point.
    @param argc Amount of arguments passed to the program.
    @param argv Argument C-string values.
    @return Exit code of the application where an exit code of 0 means
    error free.
    @see https://en.wikipedia.org/wiki/Exit_status
 */
int main(int argc, char* argv[]) {
  // Global variables
  Globals globals;
  GameObject::globals = &globals;

  // Initialize window and SDL_ttf
  globals.window =
      GPU_Init(globals.width, globals.height, SDL_WINDOW_RESIZABLE);
  TTF_Init();

  // Init music and sound
  Music::Init();

  // Load fonts
  globals.font      = TTF_OpenFont("Content/UI/alagard.ttf", 48);
  globals.smallFont = TTF_OpenFont("Content/UI/alagard.ttf", 24);

  // Create scene and input manager
  SceneManager sceneManager = SceneManager(new MainMenu());
  sceneManager.AddScene(new Music());
#ifdef DEBUG
  sceneManager.AddScene(new Stats());
#endif

  InputManager inputManager(&sceneManager, &globals);

  // Scaling coordinates
  GPU_SetVirtualResolution(globals.window, globals.vwidth, globals.vheight);

  // Main game loop
  while (globals.gameState != QUIT) {
    // Frame start time
    auto start = std::chrono::system_clock::now();
    // Process input
    inputManager.ProcessInput();

    // Clear screen
    GPU_ClearRGB(globals.window, 30, 30, 30);

    // Call scene manager tick functions
    sceneManager.Tick();

    // Flips backbuffer
    GPU_Flip(globals.window);

    // Frame end time
    auto end          = std::chrono::system_clock::now();
    auto elapsed      = end - start;
    globals.DeltaTime = ((double)elapsed.count()) / 1000000000.0;
  }

  // Quit SDL2 and SDL_gpu
  TTF_CloseFont(globals.font);
  TTF_CloseFont(globals.smallFont);
  TTF_Quit();
  GPU_Quit();
  return 0;
}

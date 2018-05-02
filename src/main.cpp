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
#include "image.hpp"
#include "input.hpp"

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

  // Initialize window
  globals.window =
      GPU_Init(globals.width, globals.height, SDL_WINDOW_RESIZABLE);

  // Create scene and input manager
  SceneManager sceneManager = SceneManager();
  InputManager inputManager(&sceneManager, &globals);

  // Create image
  Image image("Content/test_image.png", 300, 200);

  // Scaling coordinates
  GPU_SetVirtualResolution(globals.window, 1920, 1080);

  // Main game loop
  while (globals.gameState != QUIT) {
    // Process input
    inputManager.ProcessInput();

    // Clear screen
    GPU_ClearRGB(globals.window, 30, 30, 30);

    // Draw image
    image.Draw(globals.window);

    // Call scene manager tick functions
    sceneManager.Tick();

    // Flips backbuffer
    GPU_Flip(globals.window);
  }

  // Quit SDL2 and SDL_gpu
  GPU_Quit();
  return 0;
}

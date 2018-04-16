// Copyright 2018 Anas Idiab, Sebastian Winding.
// Includes
#include "globals.hpp"
#include "image.hpp"
#include "input.hpp"

// Main entry point
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

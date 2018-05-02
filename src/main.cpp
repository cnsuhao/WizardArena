// Copyright 2018 Anas Idiab, Sebastian Winding.
// Includes
#include "globals.hpp"
#include "image.hpp"
#include "input.hpp"
#include "scenes/mainmenu.hpp"

// Main entry point
int main(int argc, char* argv[]) {
  // Global variables
  Globals globals;
  GameObject::globals = &globals;

  // Initialize window and SDL_ttf
  globals.window =
      GPU_Init(globals.width, globals.height, SDL_WINDOW_RESIZABLE);
  TTF_Init();

  // Load font
  globals.font = TTF_OpenFont("Content/UI/alagard.ttf", 48);

  // Create scene and input manager
  SceneManager sceneManager = SceneManager(new MainMenu());
  InputManager inputManager(&sceneManager, &globals);

  // Scaling coordinates
  GPU_SetVirtualResolution(globals.window, globals.vwidth, globals.vheight);

  // Main game loop
  while (globals.gameState != QUIT) {
    // Process input
    inputManager.ProcessInput();

    // Clear screen
    GPU_ClearRGB(globals.window, 30, 30, 30);

    // Call scene manager tick functions
    sceneManager.Tick();

    // Flips backbuffer
    GPU_Flip(globals.window);
  }

  // Quit SDL2 and SDL_gpu
  TTF_CloseFont(globals.font);
  TTF_Quit();
  GPU_Quit();
  return 0;
}

// Copyright 2018 Anas Idiab, Sebastian Winding.
// Includes
#include "globals.hpp"
#include "image.hpp"

/*  Scene
  - Information about what to draw
  - Other relevant information, such as, selected menu item, or health
  - Get input
*/

/*  SceneManager
  - Ability to change scene
  - Ability to add scenes
*/

int main(int argc, char* argv[]) {
  // Global variables
  Globals globals;

  // Initialize window
  GPU_Target* window =
      GPU_Init(globals.width, globals.height, SDL_WINDOW_RESIZABLE);

  // Create image
  Image image("Content/test_image.png", 300, 200);

  // Allocate event memory
  SDL_Event event;

  // Scaling coordinates
  GPU_SetVirtualResolution(window, 1920, 1080);

  // Main game loop
  while (globals.gameState != QUIT) {
    // Loop through polled events
    while (SDL_PollEvent(&event)) {
      // Quits the game on quit event
      if (event.type == SDL_QUIT) { globals.gameState = QUIT; }
      // Checks if mouse motion
      if (event.type == SDL_MOUSEMOTION) {
        // Moving the image to the cursor
        image.Position = vec2(1920 * event.motion.x / globals.width,
                              1080 * event.motion.y / globals.height);
      }
      // Checks if window event
      if (event.type == SDL_WINDOWEVENT) {
        // On resize event
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
          // Store window size
          globals.width  = event.window.data1;
          globals.height = event.window.data2;
          // Set viewport size
          GPU_SetWindowResolution(event.window.data1, event.window.data2);
          // Scaling coordinates
          GPU_SetVirtualResolution(window, 1920, 1080);
        }
      }
    }
    // Clear screen
    GPU_ClearRGB(window, 30, 30, 30);

    // Draw image
    image.Draw(window);

    // Flips backbuffer
    GPU_Flip(window);
  }

  // Quit SDL2 and SDL_gpu
  GPU_Quit();
  return 0;
}

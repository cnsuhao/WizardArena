// Copyright 2018 Anas Idiab, Sebastian Winding.
// Includes
#include "includes.hpp"

// Game states enum
enum GameState { MENU = 0, GAME = 1, QUIT = 2 };

// Structure of globals
struct Globals {
  byte gameState = MENU;  // stores data
  // Screen dimensions
  uint width = 1280, height = 720;
};

/*
  Handles images
 */
class Image {
 public:
  // Loads image
  Image(const char* filename) {
    image    = GPU_LoadImage(filename);
    Position = vec2(0, 0);
  }
  // Load with position
  Image(const char* filename, vec2 Position) {
    image          = GPU_LoadImage(filename);
    this->Position = Position;
  }
  // Load with position
  Image(const char* filename, float x, float y) {
    image          = GPU_LoadImage(filename);
    this->Position = vec2(x, y);
  }
  // Destructor
  ~Image() { GPU_FreeImage(image); }

  // Draw
  void Draw(GPU_Target* target) {
    GPU_Blit(image, NULL, target, Position.x, Position.y);
  }

  vec2 Position;  // Image position

 private:
  GPU_Image* image;  // Image pointer
};

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

  // Main game loop
  while (globals.gameState != QUIT) {
    // Loop through polled events
    while (SDL_PollEvent(&event)) {
      // Quits the game on quit event
      if (event.type == SDL_QUIT) { globals.gameState = QUIT; }
      // Checks if mouse motion
      if (event.type == SDL_MOUSEMOTION) {
        // Moving the image to the cursor
        image.Position = vec2(event.motion.x, event.motion.y);
      }
      // Checks if window event
      if (event.type == SDL_WINDOWEVENT) {
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
          GPU_SetWindowResolution(event.window.data1, event.window.data2);
          // GPU_SetVirtualResolution(frametarget, 1920, 1080);
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

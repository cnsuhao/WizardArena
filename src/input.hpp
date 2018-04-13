#ifndef INPUT_H
#define INPUT_H
#include "globals.hpp"
#include "scenemanager.hpp"

/*
  Class to process input
 */
class InputManager {
 public:
  InputManager(SceneManager* sceneManager, Globals* globals) {
    this->sceneManager = sceneManager;
    this->globals      = globals;
  }
  ~InputManager() {}

  void ProcessInput() {
    // Loop through polled events
    while (SDL_PollEvent(&event)) {
      // Quits the game on quit event
      if (event.type == SDL_QUIT) { globals->gameState = QUIT; }
      // Checks if relevant SDL event
      if (event.type == SDL_MOUSEMOTION) { sceneManager->Input(event); }
      // Checks if window event
      if (event.type == SDL_WINDOWEVENT) {
        // Properly resize the framebuffer
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
          GPU_SetWindowResolution(event.window.data1, event.window.data2);
          GPU_SetVirtualResolution(globals->window, 1920, 1080);
          // Store window size
          globals->width  = event.window.data1;
          globals->height = event.window.data2;
        }
      }
    }
  }

 private:
  SceneManager* sceneManager;
  Globals*      globals;
  // Allocate event memory
  SDL_Event event;
};

#endif /* INPUT_H */

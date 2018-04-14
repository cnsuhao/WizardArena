#include "input.hpp"

InputManager::InputManager(SceneManager* sceneManager, Globals* globals) {
  this->sceneManager = sceneManager;
  this->globals      = globals;
}

InputManager::~InputManager() {}

void InputManager::ProcessInput() {
  // Loop through polled events
  while (SDL_PollEvent(&event)) {
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
    // Checks if relevant SDL event
    if (event.type == SDL_MOUSEMOTION) { sceneManager->Input(event); }
    if (event.type == SDL_MOUSEBUTTONUP) { sceneManager->Input(event); }
    if (event.type == SDL_MOUSEBUTTONDOWN) { sceneManager->Input(event); }
    if (event.type == SDL_KEYUP) {
      sceneManager->Input(event);
#ifdef DEBUG
      if (event.key.keysym.sym == SDLK_ESCAPE) { globals->gameState = QUIT; }
#endif  // DEBUG
    }
    if (event.type == SDL_KEYDOWN) { sceneManager->Input(event); }

    // Quits the game on quit event
    if (event.type == SDL_QUIT) { globals->gameState = QUIT; }
  }
}

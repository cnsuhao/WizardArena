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
        // Store window size
        globals->width  = event.window.data1;
        globals->height = event.window.data2;

        // Recreate backbuffer
        GPU_FreeTarget(globals->backbuffer);
        GPU_FreeImage(globals->backbufferImage);
        globals->backbufferImage =
            GPU_CreateImage(globals->width, globals->height, GPU_FORMAT_RGB);
        globals->backbuffer = GPU_LoadTarget(globals->backbufferImage);
        GPU_SetImageFilter(globals->backbufferImage, GPU_FILTER_NEAREST);

        // Set resolutions
        GPU_SetWindowResolution(globals->width, globals->height);
        GPU_SetVirtualResolution(globals->backbuffer, globals->vwidth,
                                 globals->vheight);
        GPU_SetVirtualResolution(globals->window, globals->width,
                                 globals->height);
      }
    }
    // Checks if relevant SDL event
    if (event.type == SDL_MOUSEMOTION) { sceneManager->Input(event); }
    if (event.type == SDL_MOUSEBUTTONUP) { sceneManager->Input(event); }
    if (event.type == SDL_MOUSEBUTTONDOWN) { sceneManager->Input(event); }
    if (event.type == SDL_KEYUP) {
      sceneManager->Input(event);
      if (event.key.keysym.sym == SDLK_F11)
        GPU_SetFullscreen(!GPU_GetFullscreen(), true);
#ifdef DEBUG
      if (event.key.keysym.sym == SDLK_ESCAPE) { globals->gameState = QUIT; }
#endif  // DEBUG
    }
    if (event.type == SDL_KEYDOWN) { sceneManager->Input(event); }

    // Quits the game on quit event
    if (event.type == SDL_QUIT) { globals->gameState = QUIT; }
  }
}

#ifndef INPUT_H
#define INPUT_H
#include "scenemanager.hpp"

/*
  Class to process input
 */
class InputManager {
 public:
  InputManager(SceneManager* sceneManager, Globals* globals);
  ~InputManager();
  void ProcessInput();

 private:
  SceneManager* sceneManager;
  Globals*      globals;
  // Allocate event memory
  SDL_Event event;
};

#endif /* INPUT_H */

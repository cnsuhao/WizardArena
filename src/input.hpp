#ifndef INPUT_H
#define INPUT_H
#include "scenemanager.hpp"

/**
  Class to process input and pass it to the SceneManager @see SceneManager.
 */
class InputManager {
 public:
  /** Constructor that saves pointers to a Globals instance and SceneManager
     instance.
      @param sceneManager Pointer to the primary SceneManager instance.
      @param globals Pointer to a Globals instance.
      @see SceneManager
      @see Globals
   */
  InputManager(SceneManager* sceneManager, Globals* globals);

  /** Destructor that does nothing for now. */
  ~InputManager();

  /** Polls all SDL events and checks for specific types. If the event has one
     of the accepted types it will trigger the SceneManager input function with
     the appropriate SDL_Event. This function also makes sure that the program
     closes when the exit button is pressed. Window resizing is also handled in
     this function.
     @see SceneManager
   */
  void ProcessInput();

 private:
  /** Pointer to the SceneManager @see SceneManager */
  SceneManager* sceneManager;
  /** Pointer to a Globals instance @see Globals */
  Globals* globals;

  /** Variable to hold event memory to avoid multiple allocations and deletions
   */
  SDL_Event event;
};

#endif /* INPUT_H */

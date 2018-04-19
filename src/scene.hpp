#ifndef SCENE_HPP
#define SCENE_HPP

#include "gameobject.hpp"

/**
  Handles a collection of game objects.
*/
class Scene {
 public:
  /** Initializes member variables. */
  Scene();

  /** Extensible destructor that deletes GameObject pointers @see GameObject */
  virtual ~Scene();

  /** Calls draw functions of all handled GameObject pointers @see GameObject.
   */

  virtual void Draw();
  /** Calls update functions of all handled GameObject pointers @see GameObject.
   */
  virtual void Update();

  /** Calls input functions of all handled GameObject pointers.
      @param event The event to pass to each GameObject.
      @see GameObject
  */
  virtual void Input(SDL_Event event);

 protected:
  // Variables
  /** Vector of GameObject pointers @see GameObject*/
  vector<GameObject*> gameObjects;
  /** Messages to pass to the SceneManager @see SceneManager */
  vector<string> messages;
  /** Lets the SceneManager see if the current scene instance is dead
   *  @see SceneManager */
  bool dead;
  // GPU_Target* target;
};

#endif /* SCENE_HPP */

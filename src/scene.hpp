#ifndef SCENE_HPP
#define SCENE_HPP

#include "gameobject.hpp"

/*
  Handels a collection of game objects.
*/
class Scene {
 public:
  // Constructor
  Scene();
  // Destructor
  virtual ~Scene();
  // Draws scene
  virtual void Draw();
  // Updates scene
  virtual void Update();
  // Processes input
  virtual void Input(SDL_Event event);

 protected:
  // Variables
  vector<GameObject*> gameObjects;
  vector<string>      messages;
  bool                dead;
  // GPU_Target* target;
};

#endif /* SCENE_HPP */

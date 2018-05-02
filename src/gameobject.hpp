#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "globals.hpp"

/*
  Game object class
 */
class GameObject {
 public:
  // Constructor
  GameObject();
  // Destructor
  virtual ~GameObject();
  // Draw GameObject
  virtual void Draw();
  // Update GameObject
  virtual void Update();
  // Input function
  virtual void Input(SDL_Event event);

  // Static variables
  static Globals* globals;

  // Variables
  vec2  position;
  vec2  size;
  float rotation;
};

#endif /* GAMEOBJECT_H */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "globals.hpp"

/*
  Game object class
 */
class GameObject {
 public:
  /** This is the constructor for GameObject.*/
  GameObject();
  /** This is the destructor for GameObject.*/
  virtual ~GameObject();
  /** This is a draw function, that draws the GameObject.*/
  virtual void Draw();
  /** This function is in charge of updating the GameObject*/
  virtual void Update();
  /** This function serves as an SDL event holder.
      @param event is a variable to hold event memory to avoid multiple allocations and deletions.
   */
  virtual void Input(SDL_Event event);
  /** This is a pointer that holds unchangeabel globals values. @see globals */
  static Globals* globals;
  /** This is a datafield, that describes the position, size and rotation of a
   * gameobject.*/
  vec2  position;
  vec2  size;
  float rotation;
};

#endif /* GAMEOBJECT_H */

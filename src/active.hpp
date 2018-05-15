#ifndef ACTIVE_H
#define ACTIVE_H
#include "gameobject.hpp"

class Active : public GameObject {
 public:
  Active() { owner = 0; }
  virtual ~Active() {}

  virtual bool Intersect(vec2 playerPosition) { return false; }

  virtual void UpdatePos(float iterations) {}

  // int  GetOwner() { return owner; }
  vec2 velocity;
  bool expired;

  int owner;
};

#endif

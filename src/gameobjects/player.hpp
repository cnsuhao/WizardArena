#ifndef PLAYER_H
#define PLAYER_H
#include "../gameobject.hpp"

class Player : public GameObject {
 public:
  Player(vec2 pos);
  ~Player();

  void Update();
  void Draw();

  float rotation;
  vec2  velocity;
  bool  dead;

 private:
  GPU_Image* image;
};

#endif

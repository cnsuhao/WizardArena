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
  float speed;

 private:
  GPU_Image* image;
};

#endif

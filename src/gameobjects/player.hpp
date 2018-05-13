#ifndef PLAYER_H
#define PLAYER_H
#include "../gameobject.hpp"

class Player : public GameObject {
 public:
  Player();
  ~Player();

  void Update();
  void Draw();

  float rotation;

 private:
  GPU_Image* image;
};

#endif

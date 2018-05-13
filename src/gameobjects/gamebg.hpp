#ifndef GAMEBG_H
#define GAMEBG_H
#include "../gameobject.hpp"
#include "image.hpp"

class GameBG : public GameObject {
 public:
  GameBG();
  ~GameBG();
  void Draw();

 private:
  Image* image;
};

#endif

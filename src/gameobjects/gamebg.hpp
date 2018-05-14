#ifndef GAMEBG_H
#define GAMEBG_H
#include "../gameobject.hpp"
#include "../shader.hpp"
#include "image.hpp"

class GameBG : public GameObject {
 public:
  GameBG();
  ~GameBG();
  void Draw();

 private:
  Image*  image;
  Shader* shader;

  map<string, uint> uniforms;
};

#endif

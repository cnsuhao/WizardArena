#ifndef SCENE_HPP
#define SCENE_HPP

#include "globals.hpp"
#include "image.hpp"

class Scene {
 public:
  Scene();
  virtual ~Scene();
  void Draw();
  void Update();

 protected:
  vector<Image*> gameObjects;

  vector<string> messages;

  bool dead;

  GPU_Target* target;
};

#endif /* SCENE_HPP */

#ifndef SCENE_HPP
#define SCENE_HPP

#include "globals.hpp"
#include "image.hpp"

class Scene {
 public:
  Scene();
  virtual ~Scene();

 protected:
  vector<Image*> gameObjects;

  vector<string> messages;

  bool dead;
};

#endif /* SCENE_HPP */

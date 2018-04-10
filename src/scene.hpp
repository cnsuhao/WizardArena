#ifndef SCENE_HPP
#define SCENE_HPP

#include "globals.hpp"
#include "image.hpp"

class Scene {
 public:
  Scene();
  vector<Image*> Scenes;

  virtual ~Scene();
};

#endif /* SCENE_HPP */

#ifndef CREDITS_H
#define CREDITS_H
#include "../gameobjects/skybg.hpp"
#include "../scene.hpp"

class Credits : public Scene {
 public:
  Credits() {
    // Add our game objects to the stack and create the sky background
    gameObjects.push_back(new SkyBG());
  }
  virtual ~Credits() {}
};

#endif /* CREDITS_H */

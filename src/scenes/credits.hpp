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

  void Draw() { Scene::Draw(); }

  void Update() { Scene::Update(); }

  void Input(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
      Dead = true;
      Messages.push_back("Main Menu");
    }
    Scene::Input(event);
  }
};

#endif /* CREDITS_H */

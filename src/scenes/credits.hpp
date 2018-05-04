#ifndef CREDITS_H
#define CREDITS_H
#include "../gameobjects/creditstext.hpp"
#include "../gameobjects/panel.hpp"
#include "../gameobjects/skybg.hpp"
#include "../scene.hpp"

class Credits : public Scene {
 public:
  Credits() {
    // Add our game objects to the stack and create the sky background
    gameObjects.push_back(new SkyBG());
    gameObjects.push_back(new Panel());
    gameObjects.push_back(new CreditsText());

    // Set position and size of panel
    gameObjects[1]->size.x = GameObject::globals->vwidth / 1.9;
    gameObjects[1]->size.y = GameObject::globals->vheight;
  }

  virtual ~Credits() {}

  void Draw() { Scene::Draw(); }

  void Update() { Scene::Update(); }

  void Input(SDL_Event event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
      Dead = true;
      Messages.push_back("Main Menu");
    }
    Scene::Input(event);
  }
};

#endif /* CREDITS_H */

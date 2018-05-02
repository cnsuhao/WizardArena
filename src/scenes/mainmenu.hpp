#ifndef MAINMENU_H
#define MAINMENU_H
#include <iostream>
#include "../gameobjects/button.hpp"
#include "../gameobjects/skybg.hpp"

class MainMenu : public Scene {
 public:
  MainMenu() {
    // Create the buttons
    buttons[0] = new Button("Play");
    buttons[1] = new Button("Options");
    buttons[2] = new Button("Credits");
    buttons[3] = new Button("Exit");

    // Add our game objects to the stack and create the sky background
    gameObjects.push_back(new SkyBG());
    gameObjects.push_back(buttons[0]);
    gameObjects.push_back(buttons[1]);
    gameObjects.push_back(buttons[2]);
    gameObjects.push_back(buttons[3]);

    // Set button positions
    buttons[0]->position = vec2(GameObject::globals->vwidth / 2, 300);
    buttons[1]->position = vec2(GameObject::globals->vwidth / 2, 400);
    buttons[2]->position = vec2(GameObject::globals->vwidth / 2, 500);
    buttons[3]->position = vec2(GameObject::globals->vwidth / 2, 600);
  };

  virtual ~MainMenu(){};

  void Update() {
    for (byte i = 0; i < 4; i++) {
      buttons[i]->SetState(i == selected ? 1 : 0);
    }

    // Call parent update function
    Scene::Update();
  }

  void Input(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_UP) {
        selected--;
        selected %= 4;
      }
      if (event.key.keysym.sym == SDLK_DOWN) {
        selected++;
        selected %= 4;
      }
      if (event.key.keysym.sym == SDLK_RETURN ||
          event.key.keysym.sym == SDLK_SPACE) {
        switch (selected) {
          case 0: buttonPlay(); break;
          case 1: buttonOptions(); break;
          case 2: buttonCredits(); break;
          case 3: buttonExit(); break;
        }
      }
    }
    // Call parent input function
    Scene::Input(event);
  }

 private:
  /**
    0: Play button
    1: Options button
    2: Credits button
    3: Exit button
   */
  Button* buttons[4];
  byte    selected = 0;

  // Button functions
  void buttonPlay() {}
  void buttonOptions() {}
  void buttonCredits() {
    Dead = true;
    Messages.push_back("Credits");
  }
  void buttonExit() { GameObject::globals->gameState = QUIT; }
};

#endif /* MAINMENU_H */

#ifndef MAINMENU_H
#define MAINMENU_H
#include "../gameobjects/button.hpp"
#include "../gameobjects/image.hpp"
#include "../gameobjects/panel.hpp"
#include "../gameobjects/skybg.hpp"
#include "../scene.hpp"

class MainMenu : public Scene {
 public:
  MainMenu() {
    // Create the buttons and panel
    buttons[0] = new Button("Play");
    buttons[1] = new Button("Options");
    buttons[2] = new Button("Credits");
    buttons[3] = new Button("Exit");
    bgpanel    = new Panel();
    logo       = new Image("Content/Textures/Logo.png",
                     GameObject::globals->vwidth / 2.0, 125);

    // Add our game objects to the stack and create the sky background
    gameObjects.push_back(new SkyBG());
    gameObjects.push_back(bgpanel);
    gameObjects.push_back(buttons[0]);
    gameObjects.push_back(buttons[1]);
    gameObjects.push_back(buttons[2]);
    gameObjects.push_back(buttons[3]);
    gameObjects.push_back(logo);

    // Set button and panel positions
    buttons[0]->position = vec2(GameObject::globals->vwidth / 2, 350);
    buttons[1]->position = vec2(GameObject::globals->vwidth / 2, 450);
    buttons[2]->position = vec2(GameObject::globals->vwidth / 2, 550);
    buttons[3]->position = vec2(GameObject::globals->vwidth / 2, 650);
    bgpanel->position.y  = GameObject::globals->vheight - 225;
    bgpanel->size        = vec2(375, 450);
    logo->size           = vec2(0.8);

    // Load menu sounds
    menuselection = Mix_LoadWAV("Content/Sound/UI/MenuSelectionClick.wav");
  }

  virtual ~MainMenu() { Mix_FreeChunk(menuselection); };

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
        Mix_PlayChannel(0, menuselection, 0);
      }
      if (event.key.keysym.sym == SDLK_DOWN) {
        selected++;
        Mix_PlayChannel(0, menuselection, 0);
      }
      selected %= 4;
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
  // Menu selection sound
  Mix_Chunk* menuselection;

  /**
    0: Play button
    1: Options button
    2: Credits button
    3: Exit button
   */
  Button* buttons[4];
  Panel*  bgpanel;
  Image*  logo;
  byte    selected = 0;

  // Button functions
  void buttonPlay() {}
  void buttonOptions() {
    Dead = true;
    Messages.push_back("Options");
  }
  void buttonCredits() {
    Dead = true;
    Messages.push_back("Credits");
  }
  void buttonExit() {
    Mix_FadeOutMusic(400);
    SDL_Delay(450);
    GameObject::globals->gameState = QUIT;
  }
};

#endif /* MAINMENU_H */

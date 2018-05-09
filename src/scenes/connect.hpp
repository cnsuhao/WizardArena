#ifndef CONNECT_H
#define CONNECT_H
#include "../gameobjects/button.hpp"
#include "../gameobjects/image.hpp"
#include "../gameobjects/panel.hpp"
#include "../gameobjects/skybg.hpp"
#include "../gameobjects/text.hpp"
#include "../scene.hpp"

/** The connect class*/
class Connect : public Scene {
 public:
  Connect() {
    // Create the buttons and panel
    buttons[0] = new Button("Connect");
    buttons[1] = new Button("Host");
    buttons[2] = new Button("Back");
    iptext     = new Text("255.255.255.255");
    bgpanel    = new Panel();
    txtpanel   = new Panel();
    logo       = new Image("Content/Textures/Logo.png",
                     GameObject::globals->vwidth / 2.0, 125);

    // Add our game objects to the stack and create the sky background
    gameObjects.push_back(new SkyBG());
    gameObjects.push_back(bgpanel);
    gameObjects.push_back(buttons[0]);
    gameObjects.push_back(buttons[1]);
    gameObjects.push_back(buttons[2]);
    gameObjects.push_back(txtpanel);
    gameObjects.push_back(iptext);
    gameObjects.push_back(logo);

    // Set button and panel positions
    buttons[0]->position = vec2(GameObject::globals->vwidth / 2, 450);
    buttons[1]->position = vec2(GameObject::globals->vwidth / 2, 550);
    buttons[2]->position = vec2(GameObject::globals->vwidth / 2, 650);
    bgpanel->position.y  = GameObject::globals->vheight - 225;
    bgpanel->size        = vec2(375, 450);
    logo->size           = vec2(0.8);
    iptext->position     = vec2(GameObject::globals->vwidth / 2, 340);
    txtpanel->position.y = 335;
    txtpanel->size       = vec2(375, 65);

    // Load menu sounds
    menuselection = Mix_LoadWAV("Content/Sound/UI/MenuSelectionClick.wav");
  }
  /** The connect destructor*/
  virtual ~Connect() { Mix_FreeChunk(menuselection); }

  /** Calls input functions of all handled GameObject pointers.
      @param event The event to pass to each GameObject.
      @see GameObject*/
  void Input(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_UP) {
        selected--;
        Mix_PlayChannel(0, menuselection, 0);
      } else if (event.key.keysym.sym == SDLK_DOWN) {
        selected++;
        Mix_PlayChannel(0, menuselection, 0);
      }
      selected %= 4;
      for (ubyte i = 0; i < 3; i++) {
        if (selected == i + 1)
          buttons[i]->SetState(1);
        else
          buttons[i]->SetState(0);
      }
      if (event.key.keysym.sym == SDLK_RETURN ||
          event.key.keysym.sym == SDLK_SPACE) {
        switch (selected) {
          case 0: break;
          case 1: buttonConnect(); break;
          case 2: buttonHost(); break;
          case 3: buttonBack(); break;
        }
      }
    }
    // Call parent input function
    Scene::Input(event);
  }

 private:
  // Menu selection sound
  Mix_Chunk* menuselection;

  /*
     0: Connect button
     1: Host button
     2: Back button
  */
  Button* buttons[3];
  Panel*  bgpanel;
  Panel*  txtpanel;
  Image*  logo;
  Text*   iptext;
  ubyte   selected = 0;

  // Button functions
  void buttonConnect() {
    Dead = true;
    Messages.push_back("Options");
  }
  void buttonHost() {
    Dead = true;
    Messages.push_back("Credits");
  }
  void buttonBack() {
    Dead = true;
    Messages.push_back("Main Menu");
  }
};

#endif  // CONNECT_H

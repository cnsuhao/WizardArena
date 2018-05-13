#ifndef LOBBY_H
#define LOBBY_H
#include "../client.hpp"
#include "../gameobjects/button.hpp"
#include "../gameobjects/image.hpp"
#include "../gameobjects/panel.hpp"
#include "../gameobjects/skybg.hpp"
#include "../gameobjects/text.hpp"
#include "../gameobjects/textbox.hpp"
#include "../scene.hpp"

/** The lobby class*/
class Lobby : public Scene {
 public:
  Lobby(Game* game, bool isServer) {
    this->game     = game;
    this->isServer = isServer;
    if (!isServer) {
      if (game->FailedToConnect) {
        Dead = true;
        Messages.push_back("Connect");
        Messages.push_back("Message");
        Messages.push_back("Failed to connect");
      }
    }

    lastPlayers = game->GetPlayerCount();

    // Create the buttons and panel
    buttons[0]   = new Button("Start game");
    buttons[1]   = new Button("Disconnect");
    bgpanel      = new Panel();
    logo         = new Image("Content/Textures/Logo.png",
                     GameObject::globals->vwidth / 2.0, 125);
    playerAmount = new Text("Players: " + std::to_string(lastPlayers));

    // Add our game objects to the stack and create the sky background
    gameObjects.push_back(new SkyBG());
    gameObjects.push_back(bgpanel);
    gameObjects.push_back(buttons[0]);
    gameObjects.push_back(buttons[1]);
    gameObjects.push_back(logo);
    gameObjects.push_back(playerAmount);

    // Set button and panel positions
    buttons[0]->position = vec2(GameObject::globals->vwidth / 2, 550);
    buttons[1]->position = vec2(GameObject::globals->vwidth / 2, 650);
    bgpanel->position.y  = GameObject::globals->vheight - 225;
    bgpanel->size        = vec2(375, 450);
    logo->size           = vec2(0.8);

    if (isServer) {
      buttons[0]->SetState(1);
    } else {
      buttons[0]->SetState(2);
      buttons[1]->SetState(1);
      selected = 1;
    }
    playerAmount->position = vec2(GameObject::globals->vwidth / 2, 340);

    // Load menu sounds
    menuselection = Mix_LoadWAV("Content/Sound/UI/MenuSelectionClick.wav");
  }
  /** The connect destructor*/
  virtual ~Lobby() {
    Mix_FreeChunk(menuselection);
    delete game;
  }

  void Update() {
    game->Update();
    if (game->GetPlayerCount() != lastPlayers) {
      lastPlayers = game->GetPlayerCount();
      playerAmount->SetText("Players: " + std::to_string(lastPlayers));
    }
    if (game->Disconnected) {
      Dead = true;
      Messages.push_back("Connect");
      Messages.push_back("Message");
      Messages.push_back("Disconnected");
    }
  }

  /** Calls input functions of all handled GameObject pointers.
      @param event The event to pass to each GameObject.
      @see GameObject*/
  void Input(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
      if (isServer) {
        if (event.key.keysym.sym == SDLK_UP) {
          selected--;
          Mix_PlayChannel(0, menuselection, 0);
        } else if (event.key.keysym.sym == SDLK_DOWN) {
          selected++;
          Mix_PlayChannel(0, menuselection, 0);
        }
        selected %= 2;
        for (ubyte i = 0; i < 2; i++) {
          if (selected == i)
            buttons[i]->SetState(1);
          else
            buttons[i]->SetState(0);
        }
      }

      if (event.key.keysym.sym == SDLK_RETURN ||
          event.key.keysym.sym == SDLK_SPACE) {
        switch (selected) {
          case 0: buttonStart(); break;
          case 1: buttonBack(); break;
        }
      }
    }

    // Call parent input function
    Scene::Input(event);
  }

  Game* game;
  bool  isServer;

 private:
  // Menu selection sound
  Mix_Chunk* menuselection;

  Button* buttons[2];
  Panel*  bgpanel;
  Image*  logo;
  Text*   playerAmount;
  ubyte   lastPlayers;

  ubyte selected = 0;

  // Button functions
  void buttonStart() {}
  void buttonBack() {
    Dead = true;
    Messages.push_back("Main Menu");
  }
};

#endif  // LOBBY_H

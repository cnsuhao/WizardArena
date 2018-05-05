#ifndef OPTIONS_H
#define OPTIONS_H
#include "../gameobjects/button.hpp"
#include "../gameobjects/image.hpp"
#include "../gameobjects/panel.hpp"
#include "../gameobjects/skybg.hpp"
#include "../gameobjects/text.hpp"
#include "../scene.hpp"
#include "../utils.hpp"

class Options : public Scene {
 public:
  Options() {
    // Highlighted color
    highlighted = {255, 255, 100, 255};

    // Create the buttons and panel
    bgpanel    = new Panel();
    logo       = new Image("Content/Textures/Logo.png",
                     GameObject::globals->vwidth / 2.0, 125);
    backbutton = new Button("Back");
    std::stringstream ss;
    ss.str("");
    ss << "Music: "
       << (int)std::round(GameObject::globals->options.MusicVolume * 100)
       << "%";
    musicText = new Text(ss.str(), highlighted, false);

    // Add our game objects to the stack and create the sky background
    gameObjects.push_back(new SkyBG());
    gameObjects.push_back(bgpanel);
    gameObjects.push_back(logo);
    gameObjects.push_back(backbutton);
    gameObjects.push_back(musicText);

    // Set button and panel positions
    bgpanel->position.y  = GameObject::globals->vheight - 225;
    bgpanel->size        = vec2(375, 450);
    logo->size           = vec2(0.8);
    backbutton->position = vec2(GameObject::globals->vwidth / 2,
                                GameObject::globals->vheight - 60);
    musicText->position  = vec2(GameObject::globals->vwidth / 2, 350);

    // Load menu sounds
    menuselection = Mix_LoadWAV("Content/Sound/UI/MenuSelectionClick.wav");
  }
  virtual ~Options() { Mix_FreeChunk(menuselection); }

  void Update() {
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
      selected %= 2;

      if (selected == 1)
        backbutton->SetState(1);
      else
        backbutton->SetState(0);

      if (selected == 0) {
        if (event.key.keysym.sym == SDLK_LEFT) {
          GameObject::globals->options.MusicVolume -= 0.05;
          Mix_VolumeMusic(GameObject::globals->options.MusicVolume *
                          MIX_MAX_VOLUME);
        }
        if (event.key.keysym.sym == SDLK_RIGHT) {
          GameObject::globals->options.MusicVolume += 0.05;
          Mix_VolumeMusic(GameObject::globals->options.MusicVolume *
                          MIX_MAX_VOLUME);
        }
        GameObject::globals->options.MusicVolume =
            clamp(GameObject::globals->options.MusicVolume, 0.0, 1.0);

        std::stringstream ss;
        ss.str("");
        ss << "Music: "
           << (int)std::round(GameObject::globals->options.MusicVolume * 100)
           << "%";
        musicText->SetText(ss.str(), highlighted);
      } else {
        std::stringstream ss;
        ss.str("");
        ss << "Music: "
           << (int)std::round(GameObject::globals->options.MusicVolume * 100)
           << "%";
        musicText->SetText(ss.str());
      }

      if (event.key.keysym.sym == SDLK_RETURN ||
          event.key.keysym.sym == SDLK_SPACE) {
        if (selected == 1) {
          Dead = true;
          Messages.push_back("Main Menu");
        }
      }
    }
    // Call parent input function
    Scene::Input(event);
  }

 private:
  // Menu selection sound
  Mix_Chunk* menuselection;

  // Game objects
  Button*   backbutton;
  Panel*    bgpanel;
  Image*    logo;
  byte      selected = 0;
  Text*     musicText;
  SDL_Color highlighted;
};

#endif  // OPTIONS_H

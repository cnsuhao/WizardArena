#ifndef OPTIONS_H
#define OPTIONS_H
#include "../gameobjects/button.hpp"
#include "../gameobjects/image.hpp"
#include "../gameobjects/panel.hpp"
#include "../gameobjects/skybg.hpp"
#include "../gameobjects/slider.hpp"
#include "../scene.hpp"
#include "../utils.hpp"

class Options : public Scene {
 public:
  Options() {
    // Create the buttons and panel
    bgpanel    = new Panel();
    logo       = new Image("Content/Textures/Logo.png",
                     GameObject::globals->vwidth / 2.0, 125);
    backbutton = new Button("Back");
    sliderMusic =
        new Slider("Music", &GameObject::globals->options.MusicVolume);
    sliderMusic->SetHighlighted(true);
    sliderSound =
        new Slider("Sound", &GameObject::globals->options.SoundVolume);

    // Add our game objects to the stack and create the sky background
    gameObjects.push_back(new SkyBG());
    gameObjects.push_back(bgpanel);
    gameObjects.push_back(logo);
    gameObjects.push_back(backbutton);
    gameObjects.push_back(sliderMusic);
    gameObjects.push_back(sliderSound);

    // Set button and panel positions
    bgpanel->position.y   = GameObject::globals->vheight - 225;
    bgpanel->size         = vec2(375, 450);
    logo->size            = vec2(0.8);
    backbutton->position  = vec2(GameObject::globals->vwidth / 2,
                                GameObject::globals->vheight - 60);
    sliderMusic->position = vec2(GameObject::globals->vwidth / 2, 350);
    sliderSound->position = vec2(GameObject::globals->vwidth / 2, 410);

    // Load menu sounds
    menuselection = Mix_LoadWAV("Content/Sound/UI/MenuSelectionClick.wav");
  }
  virtual ~Options() { Mix_FreeChunk(menuselection); }

  void Update() {
    // Call parent update function
    Scene::Update();
  }

  void Input(SDL_Event event) {
    // Call parent input function
    Scene::Input(event);

    if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_UP) {
        selected--;
        Mix_PlayChannel(0, menuselection, 0);
      }
      if (event.key.keysym.sym == SDLK_DOWN) {
        selected++;
        Mix_PlayChannel(0, menuselection, 0);
      }
      selected %= 3;

      sliderSound->SetHighlighted(false);
      sliderMusic->SetHighlighted(false);
      backbutton->SetState(0);
      switch (selected) {
        case 0: sliderMusic->SetHighlighted(true); break;
        case 1:
          sliderSound->SetHighlighted(true);
          if (event.key.keysym.sym == SDLK_LEFT ||
              event.key.keysym.sym == SDLK_RIGHT) {
            Mix_PlayChannel(0, menuselection, 0);
          }

          break;
        case 2:
          backbutton->SetState(1);
          if (event.key.keysym.sym == SDLK_RETURN ||
              event.key.keysym.sym == SDLK_SPACE) {
            Dead = true;
            Messages.push_back("Main Menu");
          }
          break;
      }

      Mix_Volume(-1, GameObject::globals->options.SoundVolume * MIX_MAX_VOLUME);
      Mix_VolumeMusic(GameObject::globals->options.MusicVolume *
                      MIX_MAX_VOLUME);
    }
  }

 private:
  // Menu selection sound
  Mix_Chunk* menuselection;

  // Game objects
  Button* backbutton;
  Panel*  bgpanel;
  Image*  logo;
  ubyte   selected = 0;
  Slider* sliderMusic;
  Slider* sliderSound;
};

#endif  // OPTIONS_H
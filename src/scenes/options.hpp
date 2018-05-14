#ifndef OPTIONS_H
#define OPTIONS_H
#include "../gameobjects/button.hpp"
#include "../gameobjects/image.hpp"
#include "../gameobjects/panel.hpp"
#include "../gameobjects/skybg.hpp"
#include "../gameobjects/slider.hpp"
#include "../options.hpp"
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
    // Slider array
    sliders[0] = new Slider("Music", &GameObject::globals->options.MusicVolume);
    sliders[0]->SetHighlighted(true);
    sliders[1] = new Slider("Sound", &GameObject::globals->options.SoundVolume);
    sliders[2] = new Slider("SSCA", &GameObject::globals->options.SSCAAmount);

    // Add our game objects to the stack and create the sky background
    gameObjects.push_back(new SkyBG());
    gameObjects.push_back(bgpanel);
    gameObjects.push_back(logo);
    gameObjects.push_back(backbutton);
    gameObjects.push_back(sliders[0]);
    gameObjects.push_back(sliders[1]);
    gameObjects.push_back(sliders[2]);

    // Set button and panel positions
    bgpanel->position.y  = GameObject::globals->vheight - 225;
    bgpanel->size        = vec2(375, 450);
    logo->size           = vec2(0.8);
    backbutton->position = vec2(GameObject::globals->vwidth / 2,
                                GameObject::globals->vheight - 60);
    // Sliders and switches
    sliders[0]->position = vec2(GameObject::globals->vwidth / 2, 350);
    sliders[1]->position = vec2(GameObject::globals->vwidth / 2, 410);
    sliders[2]->position = vec2(GameObject::globals->vwidth / 2, 470);

    // Load menu sounds
    menuselection = Mix_LoadWAV("Content/Sound/UI/MenuSelectionClick.wav");
  }
  virtual ~Options() { Mix_FreeChunk(menuselection); }

  void Update() {
    // Call parent update function
    Scene::Update();
  }

  void Input(SDL_Event event) {
    // If the mouse moved
    if (event.type == SDL_MOUSEMOTION) {
      // If the mouse is inside the button
      if (PointRectIntersect(
              vec2(((double)event.motion.x / GameObject::globals->width) *
                       GameObject::globals->vwidth,
                   ((double)event.motion.y / GameObject::globals->height) *
                       GameObject::globals->vheight),
              backbutton->size, backbutton->position)) {
        selected = 3;
        backbutton->SetState(1);
      }
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
      // If the left mouse button was pressed
      if (event.button.button == SDL_BUTTON_LEFT) {
        if (PointRectIntersect(
                vec2(((double)event.motion.x / GameObject::globals->width) *
                         GameObject::globals->vwidth,
                     ((double)event.motion.y / GameObject::globals->height) *
                         GameObject::globals->vheight),
                backbutton->size, backbutton->position)) {
          Dead = true;
          Messages.push_back("Main Menu");
          SaveOptions(GameObject::globals);
        }
      }
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {
      for (byte i = 0; i < 3; i++) {
        // If the left mouse button was pressed
        if (event.button.button == SDL_BUTTON_LEFT) {
          if (PointRectIntersect(
                  vec2(((double)event.motion.x / GameObject::globals->width) *
                           GameObject::globals->vwidth,
                       ((double)event.motion.y / GameObject::globals->height) *
                           GameObject::globals->vheight),
                  sliders[i]->size, sliders[i]->position)) {
            selected = i;
            sliders[1]->SetHighlighted(false);
            sliders[0]->SetHighlighted(false);
            sliders[2]->SetHighlighted(false);
            sliders[i]->SetHighlighted(true);
          }
        }
      }
    }

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
      selected %= 4;

      sliders[1]->SetHighlighted(false);
      sliders[0]->SetHighlighted(false);
      sliders[2]->SetHighlighted(false);
      backbutton->SetState(0);
      switch (selected) {
        case 0: sliders[0]->SetHighlighted(true); break;
        case 1:
          sliders[1]->SetHighlighted(true);
          if (event.key.keysym.sym == SDLK_LEFT ||
              event.key.keysym.sym == SDLK_RIGHT) {
            Mix_PlayChannel(0, menuselection, 0);
          }
          break;
        case 2: sliders[2]->SetHighlighted(true); break;
        case 3:
          backbutton->SetState(1);
          if (event.key.keysym.sym == SDLK_RETURN ||
              event.key.keysym.sym == SDLK_SPACE) {
            Dead = true;
            Messages.push_back("Main Menu");
            SaveOptions(GameObject::globals);
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
  /**
     0: Music slider
     1: Sound slider
     2: SSCA slider
  */
  Slider* sliders[3];
  // Game objects
  Button* backbutton;
  Panel*  bgpanel;
  Image*  logo;
  ubyte   selected = 0;
};

#endif  // OPTIONS_H

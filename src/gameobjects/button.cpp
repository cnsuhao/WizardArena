#include "button.hpp"

Button::Button(string Text) : GameObject() {
  buttonImages[0] = GPU_LoadImage("Content/UI/button.png");
  buttonImages[1] = GPU_LoadImage("Content/UI/buttonh.png");
  buttonImages[2] = GPU_LoadImage("Content/UI/buttond.png");

  SDL_Color    col = {255, 255, 255, 255};
  SDL_Surface* textsurf =
      TTF_RenderText_Blended(globals->font, Text.c_str(), col);
  buttonImages[3] = GPU_CopyImageFromSurface(textsurf);
  SDL_FreeSurface(textsurf);
  position += vec2(200);

  // Set default state
  state = 0;
}

Button::~Button() {
  GPU_FreeImage(buttonImages[0]);
  GPU_FreeImage(buttonImages[1]);
  GPU_FreeImage(buttonImages[2]);
  GPU_FreeImage(buttonImages[3]);
}

void Button::Draw() {
  GPU_Blit(buttonImages[state], nullptr, globals->window, position.x,
           position.y);
  GPU_Blit(buttonImages[3], nullptr, globals->window, position.x, position.y);
}

void Button::SetState(byte state) {
  if (state >= 0 && state <= 2) {
    this->state = state;
  } else {
    this->state = 0;
  }
}

void Button::Update() {}
void Button::Input(SDL_Event event) {}

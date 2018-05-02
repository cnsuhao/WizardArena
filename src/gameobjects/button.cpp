#include "button.hpp"

GPU_Image* Button::buttonImages[3];
bool       Button::loaded = false;

Button::Button(string Text) : GameObject() {
  if (!loaded) {
    buttonImages[0] = GPU_LoadImage("Content/UI/button.png");
    buttonImages[1] = GPU_LoadImage("Content/UI/buttonh.png");
    buttonImages[2] = GPU_LoadImage("Content/UI/buttond.png");
    loaded          = true;
  }
  SDL_Color    col = {255, 255, 255, 255};
  SDL_Surface* textsurf =
      TTF_RenderText_Blended(globals->font, Text.c_str(), col);
  buttonText = GPU_CopyImageFromSurface(textsurf);
  SDL_FreeSurface(textsurf);

  // Set default state
  state = 0;
}

Button::~Button() {
  if (loaded) {
    GPU_FreeImage(buttonImages[0]);
    GPU_FreeImage(buttonImages[1]);
    GPU_FreeImage(buttonImages[2]);
    loaded = false;
  }
  GPU_FreeImage(buttonText);
}

void Button::Draw() {
  GPU_Blit(buttonImages[state], nullptr, globals->window, position.x,
           position.y);
  GPU_Blit(buttonText, nullptr, globals->window, position.x, position.y);
}

void Button::SetState(byte state) {
  if (state >= 0 && state <= 2) {
    this->state = state;
  } else {
    this->state = 0;
  }
}

void Button::Hook(void (*f)(void)) {
  this->func = f;
  hooked     = true;
}
void Button::Update() {}
void Button::Input(SDL_Event event) {}

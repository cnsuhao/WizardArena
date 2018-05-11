#include "button.hpp"

GPU_Image* Button::buttonImages[3];
bool       Button::loaded = false;

Button::Button(string text) : GameObject() {
  if (!loaded) {
    buttonImages[0] = GPU_LoadImage("Content/UI/button.png");
    buttonImages[1] = GPU_LoadImage("Content/UI/buttonh.png");
    buttonImages[2] = GPU_LoadImage("Content/UI/buttond.png");
    loaded          = true;
  }
  buttonText = new Text(text);

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
  delete buttonText;
}

void Button::Draw() {
  buttonText->position = position;
  GPU_Blit(buttonImages[state], nullptr, globals->backbuffer, position.x,
           position.y);
  buttonText->Draw();
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

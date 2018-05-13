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

  // Save size
  size.x = buttonImages[0]->w;
  size.y = buttonImages[0]->h;

  // Load shader
  disabledShader = new Shader("Disabled", {""});

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
  delete disabledShader;
}

void Button::Draw() {
  if (state == 2) disabledShader->Activate();
  buttonText->position = position;
  GPU_Blit(buttonImages[state], nullptr, globals->backbuffer, position.x,
           position.y);
  buttonText->Draw();
  if (state == 2) disabledShader->Deactivate();
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

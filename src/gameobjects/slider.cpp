#include "slider.hpp"

const SDL_Color Slider::highlighted = {255, 255, 100, 255};

Slider::Slider(string optionName, double* valueptr) {
  option = optionName;
  valptr = valueptr;
  text   = new Text(optionToText(), false);
  size   = text->size;
}

Slider::~Slider() { delete text; }

void Slider::Draw() {
  text->position = position;
  text->Draw();
}

void Slider::Input(SDL_Event event) {
  if (event.type == SDL_KEYDOWN && isHighlighted) {
    if (event.key.keysym.sym == SDLK_LEFT) { *valptr -= 0.05; }
    if (event.key.keysym.sym == SDLK_RIGHT) { *valptr += 0.05; }
    *valptr = clamp(*valptr, 0.0, 1.0);
    text->SetText(optionToText(), highlighted);
  }
}

void Slider::SetHighlighted(bool isHighlighted) {
  this->isHighlighted = isHighlighted;
  if (isHighlighted)
    text->SetText(optionToText(), highlighted);
  else
    text->SetText(optionToText());
  size = text->size;
}

string Slider::optionToText() {
  return option + ": " + std::to_string((int)std::round(*valptr * 100)) + "%";
}

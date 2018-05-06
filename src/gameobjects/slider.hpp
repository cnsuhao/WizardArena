#ifndef SLIDER_H
#define SLIDER_H
#include "../gameobject.hpp"
#include "../utils.hpp"
#include "text.hpp"

class Slider : public GameObject {
 public:
  Slider(string optionName, double* value);
  ~Slider();

  void Draw();
  void Input(SDL_Event event);
  void SetHighlighted(bool isHighlighted);

 private:
  static const SDL_Color highlighted;

  double* valptr;
  string  option;
  bool    isHighlighted;

  Text* text;

  string optionToText();
};

#endif  // SLIDER_H

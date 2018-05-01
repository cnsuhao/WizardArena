#ifndef BUTTON_H
#define BUTTON_H
#include "../gameobject.hpp"
#include "../includes.hpp"

class Button : public GameObject {
 public:
  Button(string Text);
  virtual ~Button();
  // Draw GameObject
  void Draw() override;
  // Update GameObject
  void Update() override;
  // Input function
  void Input(SDL_Event event) override;

  void SetState(byte state);

 private:
  /* 0: default
     1: highlighted
     2: down
     3: text
   */
  GPU_Image* buttonImages[4];

  // Current state
  byte state;
};

#endif /* BUTTON_H */

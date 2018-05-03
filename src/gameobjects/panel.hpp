#ifndef PANEL_H
#define PANEL_H
#include "../gameobject.hpp"

class Panel : public GameObject {
 public:
  Panel();
  Panel(SDL_Color color);
  virtual ~Panel();

  // Draw GameObject
  void Draw();

 private:
  GPU_Image* panel;
};

#endif  // PANEL_H

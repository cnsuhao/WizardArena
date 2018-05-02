#ifndef PANEL_H
#define PANEL_H
#include "../gameobject.hpp"

class Panel : public GameObject {
 public:
  Panel();
  virtual ~Panel();

  // Draw GameObject
  void Draw();
};

#endif  // PANEL_H

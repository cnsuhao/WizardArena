#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "../gameobject.hpp"
#include "../gameobjects/panel.hpp"
#include "../gameobjects/text.hpp"

class Textbox : public GameObject {
 public:
  Textbox(string startText, bool highlighted);
  ~Textbox();
  void SetHighlighted(bool highlighted);
  void Input(SDL_Event event);
  void Draw();

  string GetText() { return txt; };

 private:
  Text*  text;
  Panel* txtpanel;
  Panel* cursorpanel;
  bool   highlighted;

  string txt;
};

#endif

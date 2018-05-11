#ifndef TEXT_H
#define TEXT_H
#include "../gameobject.hpp"
#include "../includes.hpp"

class Text : public GameObject {
 public:
  Text(string text);
  Text(string text, bool useSmallFont);
  Text(string text, SDL_Color color);
  Text(string text, SDL_Color color, bool useSmallFont);
  virtual ~Text();
  void Draw();
  void SetText(string text);
  void SetText(string text, bool useSmallFont);
  void SetText(string text, SDL_Color color);
  void SetText(string text, SDL_Color color, bool useSmallFont);

  string GetLastText() { return lastText; }

 private:
  GPU_Image* textimg;
  string     lastText;
};

#endif /* TEXT_H */

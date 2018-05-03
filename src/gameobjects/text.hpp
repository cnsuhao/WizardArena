#ifndef TEXT_H
#define TEXT_H
#include "../gameobject.hpp"
#include "../includes.hpp"

class Text : public GameObject {
 public:
  Text(string text);
  Text(string text, SDL_Color color);
  virtual ~Text();
  void Draw();
  void SetText(string text);
  void SetText(string text, SDL_Color color);

 private:
  GPU_Image* textimg;
};

#endif /* TEXT_H */

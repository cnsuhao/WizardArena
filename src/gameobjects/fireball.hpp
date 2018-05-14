#ifndef FIREBALL_H
#define FIREBALL_H
#include "../active.hpp"

class Fireball : public Active {
 public:
  Fireball(int owner, vec2 position, vec2 velocity);
  ~Fireball();

  void Update();
  void Draw();
  bool Intersect(vec2 playerPosition);

 private:
  GPU_Image* img;

  double birthTime;
};

#endif
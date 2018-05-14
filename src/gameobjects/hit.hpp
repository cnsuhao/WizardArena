#ifndef HIT_HPP
#define HIT_HPP
#include "../active.hpp"
#include "player.hpp"

class Hit : public Active {
 public:
  Hit(int Owner);
  ~Hit();

  void Update();
  void Draw();
};

#endif

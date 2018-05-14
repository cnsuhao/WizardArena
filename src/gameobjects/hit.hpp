#ifndef HIT_HPP
#define HIT_HPP
#include "player.hpp"

class Hit : public GameObject {
 public:
  Hit(int Owner);
  ~Hit();
  int GetOwner();

  void Update();
  void Draw();

 private:
  int owner;
};

#endif

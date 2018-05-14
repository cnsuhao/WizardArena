#ifndef PLAYER_H
#define PLAYER_H
#include "../gameobject.hpp"
#include "panel.hpp"

#define VOIDDEATHTIME 1
#define COOLDOWNTIME 0.4

class Player : public GameObject {
 public:
  Player(vec2 pos);
  ~Player();

  void Update();
  void Draw();
  void Cooldown();

  float rotation;
  vec2  velocity;
  bool  dead;
  bool  poweredUp;
  bool  coolingDown;

  // Damage related
  float damageTaken;
  vec2  acceleration;

 private:
  GPU_Image* image;

  Panel* deathTimer;
  double voidTime;     // Time in void in seconds
  double powerUpTime;  // Timestamp for powerup event
  double actionTime;   // Time of last action
};

#endif

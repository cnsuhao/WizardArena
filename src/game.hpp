#ifndef GAME_H
#define GAME_H
#include "includes.hpp"

class Game {
 public:
  Game() { playerPositions = vector<vec2>(); };
  virtual ~Game();

  vector<vec2> GetPlayerPositions() { return playerPositions; }

 protected:
  volatile vector<vec2> playerPositions;

  thread* gameThread;
  mutex*  sharedMutex;
};

#endif

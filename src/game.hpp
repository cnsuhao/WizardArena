#ifndef GAME_H
#define GAME_H
#include "includes.hpp"

class Game {
 public:
  Game() {
    playerPositions = vector<vec2>();
    playerRotations = vector<float>();
  };

  virtual ~Game() {}

  virtual void StartGame() {}
  virtual void Update() {}
  virtual void Input(SDL_Event event) {}

  vector<vec2>  GetPlayerPositions() { return playerPositions; }
  vector<float> GetPlayerRotations() { return playerRotations; }

 protected:
  // Game
  vector<vec2>  playerPositions;
  vector<float> playerRotations;

  // Threading
  thread* gameThread;
  mutex*  sharedMutex;

  // Networking
  TCPsocket socket;
};

#endif

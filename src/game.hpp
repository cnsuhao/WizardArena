#ifndef GAME_H
#define GAME_H
#include "gameobjects/player.hpp"
#include "includes.hpp"

#define MAX_SPEED 1000.0f

class Game {
 public:
  Game() { Players = vector<Player*>(); };

  virtual ~Game() {
    for (int i = 0; i < Players.size(); i++) delete Players[i];
    Players.clear();
  }

  virtual void StartGame() {}
  virtual void Update() {}
  virtual void Input(SDL_Event event) {}
  virtual int  GetPlayerIndex() { return 0; }
  virtual int  GetPlayerCount() { return 0; }

  vector<Player*> Players;

  // Flags
  bool FailedToConnect = false;
  bool Disconnected    = false;
  bool GameStarted     = false;

 protected:
  // Threading
  // thread* gameThread;
  // mutex*  sharedMutex;

  // Networking
  TCPsocket socket;
};

#endif

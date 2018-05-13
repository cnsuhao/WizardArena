#ifndef GAME_H
#define GAME_H
#include "gameobjects/player.hpp"
#include "includes.hpp"

class Game {
 public:
  Game() { Players = vector<Player*>(); };

  virtual ~Game() {}

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

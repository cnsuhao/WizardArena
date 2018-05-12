#ifndef SERVER_H
#define SERVER_H
#include "game.hpp"

const unsigned short MAX_SOCKETS = 4;
const unsigned short MAX_CLIENTS = MAX_SOCKETS - 1;
const unsigned short PORT        = 1248;
const unsigned short BUFFER_SIZE = 512;

const string SERVER_NOT_FULL = "OK";
const string SERVER_FULL     = "FULL";

class Server : public Game {
 public:
  Server();
  ~Server();

  void StartGame();
  void Update();

 private:
  IPaddress serverIP;
  TCPsocket clientSocket[MAX_CLIENTS];
  bool      socketIsFree[MAX_CLIENTS];
  char      buffer[BUFFER_SIZE];
  int       receivedByteCount = 0;
  int       clientCount       = 0;

  SDLNet_SocketSet socketSet;
};

#endif  // SERVER_H

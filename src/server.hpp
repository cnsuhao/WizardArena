#ifndef SERVER_H
#define SERVER_H
#include "game.hpp"

const unsigned short PORT        = 1248;
const unsigned short BUFFER_SIZE = 512;

class Server : public Game {
 public:
  Server();
  ~Server();

  void StartGame();
  void Update();
  int  GetPlayerIndex();
  int  GetPlayerCount();

 private:
  static const unsigned short MAX_SOCKETS = 4;
  static const unsigned short MAX_CLIENTS = MAX_SOCKETS - 1;

  const string SERVER_NOT_FULL = "OK";
  const string SERVER_FULL     = "FULL";

  IPaddress serverIP;
  TCPsocket clientSocket[MAX_CLIENTS];
  bool      socketIsFree[MAX_CLIENTS];
  char      buffer[BUFFER_SIZE];
  int       receivedByteCount = 0;
  int       clientCount       = 0;

  SDLNet_SocketSet socketSet;

  void SendMessage(int id, string msg);
  void SendMessageAll(string msg);

  string playersToString();
};
#endif  // SERVER_H

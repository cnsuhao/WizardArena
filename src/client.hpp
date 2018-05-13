#ifndef CLIENT_H
#define CLIENT_H
#include "server.hpp"

class Client : public Game {
 public:
  Client(string ipAddress);
  ~Client();

  void Update();
  int  GetPlayerIndex();
  int  GetPlayerCount();

 private:
  const char* host;  // Where we store the host name

  IPaddress serverIP;      //< The IP we will connect to
  TCPsocket clientSocket;  //< The socket to use
  string    serverName;    ///< The server name

  SDLNet_SocketSet socketSet;

  string userInput   = "";  ///< A string to hold our packet data
  int    inputLength = 0;
  char   buffer[BUFFER_SIZE];

  // Lobby
  int playerCount;

  void SendMessage(string message);
};

#endif

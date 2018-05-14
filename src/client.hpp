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
  UDPConnection*   connection;

  string userInput   = "";  ///< A string to hold our packet data
  int    inputLength = 0;
  char   buffer[BUFFER_SIZE];

  // Lobby
  int    playerCount;
  int    playerIndex;
  double gameStartTime;

  void SendMessage(string message);
  void ProcessMessage(string message);
  void startGame(string message);
  void addPlayer(string info);
  void updatePlayer(string info);
  void sendStatus();
};

#endif

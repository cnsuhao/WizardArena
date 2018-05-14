#include "server.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::to_string;

Server::Server() {
  receivedByteCount = 0;
  clientCount       = 0;

  // Create socket set
  socketSet = SDLNet_AllocSocketSet(MAX_SOCKETS);
  if (socketSet == NULL) {
    cout << "Failed to allocate the socket set: " << SDLNet_GetError() << "\n";
    return;
  } else {
    cout << "Allocated socket set with size:  " << MAX_SOCKETS << ", of which "
         << MAX_CLIENTS << " are availble for use by clients." << endl;
  }

  // Blank all client sockets
  for (int i = 0; i < MAX_CLIENTS; i++) {
    clientSocket[i] = NULL;
    socketIsFree[i] = true;
  }

  // Resolve local ip host
  int hostResolved = SDLNet_ResolveHost(&serverIP, NULL, PORT);
  if (hostResolved == -1) {
    cout << "Failed to resolve the server host: " << SDLNet_GetError() << endl;
  } else {
    Uint8* dotQuad = (Uint8*)&serverIP.host;
    cout << "Successfully resolved server host to IP: "
         << (unsigned short)dotQuad[0] << "." << (unsigned short)dotQuad[1]
         << "." << (unsigned short)dotQuad[2] << "."
         << (unsigned short)dotQuad[3];
    cout << " port " << SDLNet_Read16(&serverIP.port) << endl << endl;
  }

  // Try to open the server socket
  socket = SDLNet_TCP_Open(&serverIP);
  if (!socket) {
    cout << "Failed to open the server socket: " << SDLNet_GetError() << "\n";
    return;
  } else {
    cout << "Sucessfully created server socket." << endl;
  }

  // Add our server socket to the socket set
  SDLNet_TCP_AddSocket(socketSet, socket);
}

void Server::Update() {
  //  0: dont wait
  //  any other number is a number of milliseconds
  SDLNet_CheckSockets(socketSet, 0);

  // Check if our server socket has received any data
  int serverSocketActivity = SDLNet_SocketReady(socket);
  if (serverSocketActivity) {
    // If we have room for more clients...
    if (clientCount < MAX_CLIENTS && !GameStarted) {
      // Find the first free socket in our array of client sockets
      int freeSpot = -99;
      for (int i = 0; i < MAX_CLIENTS; i++) {
        if (socketIsFree[i] == true) {
          socketIsFree[i] = false;
          freeSpot        = i;
          break;
        }
      }
      // Accept client connection
      clientSocket[freeSpot] = SDLNet_TCP_Accept(socket);
      // Add new client socket to the socket set
      SDLNet_TCP_AddSocket(socketSet, clientSocket[freeSpot]);
      // Increase our client count
      clientCount++;
      // Send "OK" to client
      SendMessage(freeSpot, SERVER_NOT_FULL);
      // Update player count
      for (int j = 0; j < MAX_CLIENTS; j++) {
        if (!socketIsFree[j]) {
          SendMessage(j, "C" + std::to_string(GetPlayerCount()));
        }
      }
    } else {
      TCPsocket tmpSock = SDLNet_TCP_Accept(socket);
      // Accept, reject and disconnect from client
      if (GameStarted) {
        strcpy(buffer, "GP");
      } else {
        cout << "Maximum client count reached" << endl;
        strcpy(buffer, SERVER_FULL.c_str());
      }
      SDLNet_TCP_Send(tmpSock, (void*)buffer, strlen(buffer) + 1);
      SDLNet_TCP_Close(tmpSock);
    }
  }

  // Loop to check all possible client sockets for activity
  for (int clientNumber = 0; clientNumber < MAX_CLIENTS; clientNumber++) {
    int clientSocketActivity = SDLNet_SocketReady(clientSocket[clientNumber]);

    // If there is any activity on client socket
    if (clientSocketActivity) {
      receivedByteCount =
          SDLNet_TCP_Recv(clientSocket[clientNumber], buffer, BUFFER_SIZE);

      // If activity, but no data, then client has disconnected
      if (receivedByteCount <= 0) {
        cout << "Client " << clientNumber << " disconnected." << endl << endl;

        Players[clientNumber + 1]->dead = true;

        // Remove socket from socket set, close and reset socket
        SDLNet_TCP_DelSocket(socketSet, clientSocket[clientNumber]);
        SDLNet_TCP_Close(clientSocket[clientNumber]);
        clientSocket[clientNumber] = NULL;
        socketIsFree[clientNumber] = true;
        clientCount--;

        // Update player count
        SendMessageAll("C" + std::to_string(GetPlayerCount()));
      } else {
        // Process messages
        if (!strcmp(buffer, "PC")) {
          SendMessage(clientNumber, "C" + std::to_string(GetPlayerCount()));
        }
        string msg(buffer, receivedByteCount);
        // if (GameStarted) processPlayerMessage(clientNumber, msg);
      }
    }
  }
  if (GameStarted) { SendGameUpdate(); }
}

void Server::SendGameUpdate() { SendMessageAll(playersToString()); }

void Server::processPlayerMessage(int id, string msg) {
  if (msg == "") return;
  vector<string> parts = vector<string>();

  string buf = "";
  for (uint i = 0; i < msg.size(); i++) {
    if (msg[i] == '#') {
      parts.push_back(buf);
      buf = "";
    } else {
      buf += msg[i];
    }
  }
  parts.push_back(buf);
  Players[id + 1]->position.x = std::stof(parts[0]);
  Players[id + 1]->position.y = std::stof(parts[1]);
  Players[id + 1]->rotation   = std::stof(parts[2]);
  Players[id + 1]->velocity.x = std::stof(parts[3]);
  Players[id + 1]->velocity.y = std::stof(parts[4]);
}

void Server::StartGame() {
  for (int i = 0; i < clientCount + 1; i++) {
    Players.push_back(new Player(vec2(400 + 200 * i, 50 + 300 * i)));
  }

  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (!socketIsFree[i]) {
      connections.push_back(new UDPConnection());
      connections[i]->Init("0.0.0.0", 1248 + i + 10, 1248 + i);
      SendMessage(i, "GS" + std::to_string(i + 1) +
                         std::to_string(clientCount + 1) +
                         std::to_string((uint)1248 + i + 10) +
                         std::to_string((uint)1248 + i));
    }
  }

  GameStarted = true;
  SDL_Delay(60);
}

Server::~Server() {
  // DC everyone
  for (int j = 0; j < MAX_CLIENTS; j++) {
    if (!socketIsFree[j]) { SendMessage(j, "DC"); }
  }

  for (int i = 0; i < connections.size(); i++) { delete connections[i]; }
  connections.clear();

  // Free socket set
  SDLNet_FreeSocketSet(socketSet);

  // Close server socket
  SDLNet_TCP_Close(socket);
}

int Server::GetPlayerIndex() { return 0; }
int Server::GetPlayerCount() { return clientCount + 1; }

void Server::SendMessage(int id, string msg) {
  if (socketIsFree[id]) return;
  strcpy(buffer, msg.c_str());
  SDLNet_TCP_Send(clientSocket[id], (void*)buffer, strlen(buffer) + 1);
}
void Server::SendMessageAll(string msg) {
  if (GameStarted) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
      if (!socketIsFree[i]) { connections[i]->Send(msg); }
    }
  } else {
    for (int j = 0; j < MAX_CLIENTS; j++) {
      if (!socketIsFree[j]) { SendMessage(j, msg); }
    }
  }
}
/*void Server::SendMessageAll(string msg) {
  for (int j = 0; j < MAX_CLIENTS; j++) {
    if (!socketIsFree[j]) { SendMessage(j, msg); }
  }
}*/

string Server::playersToString() {
  string tmp = "";
  for (int i = 0; i < Players.size(); i++) {
    if (Players[i]->dead) {
      tmp += "P" + to_string(i) + "D";
    } else {
      tmp += "P" + to_string(i) + to_string(Players[i]->position.x) + "#" +
             to_string(Players[i]->position.y) + "#" +
             to_string(Players[i]->rotation) + "#" +
             to_string(Players[i]->velocity.x) + "#" +
             to_string(Players[i]->velocity.y);
    }
  }
  return tmp;
}

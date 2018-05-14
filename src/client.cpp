#include "client.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::to_string;

Client::Client(string ipAddress) {
  serverName  = ipAddress;
  playerCount = 0;
  playerIndex = 0;

  // Create the socket set
  socketSet = SDLNet_AllocSocketSet(1);
  if (socketSet == NULL) {
    cout << "Failed to allocate the socket set: " << SDLNet_GetError() << "\n";
    FailedToConnect = true;
    return;
  } else {
    cout << "Successfully allocated socket set." << endl;
  }

  // Try to resolve the host
  if (SDLNet_ResolveHost(&serverIP, serverName.c_str(), PORT) == -1) {
    cout << "Failed to resolve the server hostname: " << SDLNet_GetError()
         << "\nContinuing...\n";
  } else {
    // Cast IP address to dot-quad format
    Uint8* dotQuad = (Uint8*)&serverIP.host;
    cout << "Successfully resolved host to IP: " << (unsigned short)dotQuad[0]
         << "." << (unsigned short)dotQuad[1] << "."
         << (unsigned short)dotQuad[2] << "." << (unsigned short)dotQuad[3];
    cout << " port " << SDLNet_Read16(&serverIP.port) << endl;
  }

  // Resolve the IP of the server
  if ((host = SDLNet_ResolveIP(&serverIP)) == NULL) {
    cout << "Failed to resolve IP address: " << SDLNet_GetError() << endl;
  } else {
    cout << "Successfully resolved IP to host: " << host << endl;
  }

  // Try to open a connection to the server and quit out if we can't connect
  clientSocket = SDLNet_TCP_Open(&serverIP);
  if (!clientSocket) {
    cout << "Failed to open socket to server: " << SDLNet_GetError() << "\n";
    FailedToConnect = true;
    return;
  } else {
    cout << "Connection okay..." << endl;
    // Add our socket to the socket set for polling
    SDLNet_TCP_AddSocket(socketSet, clientSocket);

    // Wait for up to five seconds for a response from the server
    SDLNet_CheckSockets(socketSet, 5000);

    // Check if we got a response from the server
    if (SDLNet_SocketReady(clientSocket) != 0) {
      SDLNet_TCP_Recv(clientSocket, buffer, BUFFER_SIZE);
      cout << "Response: " << buffer << endl;

      // Check if we got an ok
      if (strcmp(buffer, "OK") == 0) {
        cout << "Joining server now..." << endl << endl;
        SendMessage("PC");
      } else {
        cout << "Server is full..." << endl;
        FailedToConnect = true;
      }
    } else {
      cout << "No response from server..." << endl;
      FailedToConnect = true;
    }
  }
}

Client::~Client() { SDLNet_TCP_Close(clientSocket); }

void Client::Update() {
  if (GameStarted) sendStatus();

  // Check our socket set for activity.
  if (SDLNet_CheckSockets(socketSet, 0) != 0) {
    // Check if we got a response from the server
    if (SDLNet_SocketReady(clientSocket) != 0) {
      int msglen = SDLNet_TCP_Recv(clientSocket, buffer, BUFFER_SIZE);
      // Check for DC
      if (strcmp(buffer, "DC") == 0) { Disconnected = true; }

      // Convert to c++ string
      string msg(buffer, msglen);
      if (msg[0] == 'C') playerCount = std::stoi(msg.substr(1, msg.size() - 1));
      if (GameStarted) ProcessMessage(msg);
      if (msg.substr(0, 2) == "GS") { startGame(msg); }
    }
  }
}

int Client::GetPlayerIndex() { return playerIndex; }
int Client::GetPlayerCount() { return playerCount; }

void Client::SendMessage(string message) {
  strcpy(buffer, message.c_str());
  SDLNet_TCP_Send(clientSocket, (void*)buffer, strlen(buffer) + 1);
}

void Client::sendStatus() {
  SendMessage(to_string(Players[playerIndex]->position.x) + "|" +
              to_string(Players[playerIndex]->position.y) + "|" +
              to_string(Players[playerIndex]->rotation) + "|" +
              to_string(Players[playerIndex]->velocity.x) + "|" +
              to_string(Players[playerIndex]->velocity.y));
}

void Client::ProcessMessage(string message) {
  string buf = "";
  for (uint i = 0; i < message.size(); i++) {
    if (message[i] == 'P') {
      updatePlayer(buf);
      buf = "";
    } else {
      buf += message[i];
    }
  }
  updatePlayer(buf);
}

void Client::updatePlayer(string info) {
  // Check if there is something to process
  if (info == "") return;

  string buf   = {info[0]};
  int    index = std::stoi(buf);

  // Check if dead
  if (info[1] == 'D') {
    Players[index]->dead = true;
    return;
  }

  // Check if local player
  if (index == playerIndex || index >= Players.size()) return;
  buf = "";

  vector<string> parts = vector<string>();

  buf = "";
  for (uint i = 1; i < info.size(); i++) {
    if (info[i] == '|') {
      parts.push_back(buf);
      buf = "";
    } else {
      buf += info[i];
    }
  }
  parts.push_back(buf);
  buf = "";
  try {
    Players[index]->position.x = std::stof(parts[0]);
    buf += "a";
    Players[index]->position.y = std::stof(parts[1]);
    buf += "a";
    Players[index]->rotation = std::stof(parts[2]);
    buf += "a";
    Players[index]->velocity.x = std::stof(parts[3]);
    buf += "a";
    Players[index]->velocity.y = std::stof(parts[4]);
  } catch (const std::exception& e) {
    cout << "EXCEPTION AT: " << buf << endl;
    cout << "Part 0: " << parts[0] << endl;
    cout << "Part 1: " << parts[1] << endl;
    cout << "Part 2: " << parts[2] << endl;
    cout << "Part 3: " << parts[3] << endl;
    cout << "Part 4: " << parts[4] << endl;
  }
}

void Client::addPlayer(string info) {
  if (info == "") return;
  vector<string> parts = vector<string>();
  string         buf   = "";
  for (uint i = 1; i < info.size(); i++) {
    if (info[i] == '|') {
      parts.push_back(buf);
      buf = "";
    } else {
      buf += info[i];
    }
  }
  parts.push_back(buf);
  Players.push_back(new Player(vec2(std::stof(parts[0]), std::stof(parts[1]))));
}

void Client::startGame(string message) {
  GameStarted = true;

  // Get player index
  string buf  = {message[2]};
  playerIndex = std::stoi(buf);
  buf         = "";

  // Add players to local vector
  for (uint i = 3; i < message.size(); i++) {
    if (message[i] == 'P') {
      addPlayer(buf);
      buf = "";
    } else {
      buf += message[i];
    }
  }
  addPlayer(buf);
  sendStatus();
}

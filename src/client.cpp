#include "client.hpp"
#include <iostream>

using std::cout;
using std::endl;

Client::Client(string ipAddress) {
  serverName  = ipAddress;
  playerCount = 0;

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
    }
  }
}

int Client::GetPlayerIndex() { return 0; }
int Client::GetPlayerCount() { return playerCount; }

void Client::SendMessage(string message) {
  strcpy(buffer, message.c_str());
  SDLNet_TCP_Send(clientSocket, (void*)buffer, strlen(buffer) + 1);
}

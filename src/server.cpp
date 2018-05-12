#include "server.hpp"
#include <iostream>

using std::cout;
using std::endl;

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

void Server::StartGame() {}

void Server::Update() {
  //  0 means do not wait (high CPU!)
  // -1 means wait for up to 49 days
  // any other number is a number of milliseconds
  int numActiveSockets = SDLNet_CheckSockets(socketSet, 0);

  if (numActiveSockets != 0) {
    cout << "There are currently " << numActiveSockets
         << " socket(s) with data to be processed." << endl;
  }

  // Check if our server socket has received any data
  int serverSocketActivity = SDLNet_SocketReady(socket);

  // If there is activity on server socket
  if (serverSocketActivity) {
    // If we have room for more clients...
    if (clientCount < MAX_CLIENTS) {
      // Find the first free socket in our array of client sockets
      int freeSpot = -99;
      for (int i = 0; i < MAX_CLIENTS; i++) {
        if (socketIsFree[i] == true) {
          // cout << "Found a free spot at element: " << i << endl;
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
      strcpy(buffer, SERVER_NOT_FULL.c_str());
      int msgLength = strlen(buffer) + 1;
      SDLNet_TCP_Send(clientSocket[freeSpot], (void*)buffer, msgLength);

      cout << "Client connected. There are now " << clientCount
           << " client(s) connected." << endl
           << endl;
    } else {
      cout << "*** Maximum client count reached - rejecting client connection "
              "***"
           << endl;

      // Accept, reject and disconnect from client
      TCPsocket tmpSock = SDLNet_TCP_Accept(socket);

      strcpy(buffer, SERVER_FULL.c_str());
      int msgLength = strlen(buffer) + 1;
      SDLNet_TCP_Send(tmpSock, (void*)buffer, msgLength);

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

        // Remove socket from socket set, close and reset socket
        SDLNet_TCP_DelSocket(socketSet, clientSocket[clientNumber]);
        SDLNet_TCP_Close(clientSocket[clientNumber]);
        clientSocket[clientNumber] = NULL;
        socketIsFree[clientNumber] = true;
        clientCount--;

        cout << "Server is now connected to: " << clientCount << " client(s)."
             << endl
             << endl;
      } else {
        // Output the message the server received to the screen
        cout << "Received: >>>> " << buffer
             << " from client number: " << clientNumber << endl;

        // Send message to all other connected clients
        int originatingClient = clientNumber;

        for (int j = 0; j < MAX_CLIENTS; j++) {
          int msgLength = strlen(buffer) + 1;

          if (msgLength > 1 && j != originatingClient && !socketIsFree[j]) {
            cout << "Retransmitting message: " << buffer << " (" << msgLength
                 << " bytes) to client number: " << j << endl;
            SDLNet_TCP_Send(clientSocket[j], (void*)buffer, msgLength);
          }
        }
      }
    }
  }
}

Server::~Server() {
  // Free socket set
  SDLNet_FreeSocketSet(socketSet);

  // Close server socket
  SDLNet_TCP_Close(socket);
}

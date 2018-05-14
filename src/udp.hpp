#include <iostream>
#include "includes.hpp"

class UDPConnection {
 public:
  UDPConnection() {}
  ~UDPConnection() {
    SDLNet_FreePacket(packet);
    SDLNet_Quit();
  }

  bool Init(const std::string& ip, int32_t remotePort, int32_t localPort) {
    std::cout << "Connecting to \n\tIP : " << ip << "\n\tPort : " << remotePort
              << std::endl;
    std::cout << "Local port : " << localPort << "\n\n";

    // Initialize udp connection
    if (!OpenPort(localPort)) return false;
    if (!SetIPAndPort(ip, remotePort)) return false;
    if (!CreatePacket(512)) return false;

    return true;
  }

  bool CreatePacket(int32_t packetSize) {
    std::cout << "Creating packet with size " << packetSize << "...\n";

    // Allocate memory for the packet
    packet = SDLNet_AllocPacket(packetSize);
    if (packet == nullptr) {
      std::cout << "\tSDLNet_AllocPacket failed : " << SDLNet_GetError()
                << std::endl;
      return false;
    }
    // Set the destination host and port
    // We got these from calling SetIPAndPort()
    packet->address.host = serverIP.host;
    packet->address.port = serverIP.port;
    std::cout << "\tSuccess!\n\n";
    return true;
  }
  bool OpenPort(int32_t port) {
    std::cout << "Opening port " << port << "...\n";

    // Sets our sovket with our local port
    ourSocket = SDLNet_UDP_Open(port);

    if (ourSocket == nullptr) {
      std::cout << "\tSDLNet_UDP_Open failed : " << SDLNet_GetError()
                << std::endl;
      return false;
    }

    std::cout << "\tSuccess!\n\n";
    return true;
  }
  bool SetIPAndPort(const std::string& ip, uint16_t port) {
    std::cout << "Setting IP ( " << ip << " ) "
              << "and port ( " << port << " )\n";

    // Set IP and port number with correct endianess
    if (SDLNet_ResolveHost(&serverIP, ip.c_str(), port) == -1) {
      std::cout << "\tSDLNet_ResolveHost failed : " << SDLNet_GetError()
                << std::endl;
      return false;
    }

    std::cout << "\tSuccess!\n\n";
    return true;
  }
  // Send data.
  bool Send(const std::string& msg) {
    // Set the data
    memcpy(packet->data, msg.c_str(), msg.length());
    packet->len = msg.length();

    // Send
    // SDLNet_UDP_Send returns number of packets sent. 0 means error
    if (SDLNet_UDP_Send(ourSocket, -1, packet) == 0) {
      std::cout << "\tSDLNet_UDP_Send failed : " << SDLNet_GetError() << "\n";
      return false;
    }
    return true;
  }

  string CheckForData() {
    // Check t see if there is a packet wauting for us...
    if (SDLNet_UDP_Recv(ourSocket, packet)) {
      std::string tmp((char*)packet->data, packet->len);
      // std::cout << "\tData received : " << tmp << "\n";
      return tmp;
    }
    return "";
  }

 private:
  UDPsocket  ourSocket;
  IPaddress  serverIP;
  UDPpacket* packet;
};

#pragma once

#include <arpa/inet.h> // inet_pton()
#include <cerrno>      //errno
#include <cstdio>      //perror()
#include <cstdio>
#include <cstring> // memset()
#include <cstring>
#include <iostream>
#include <netinet/in.h> //sockaddr_in()
#include <pthread.h>
#include <string>
#include <sys/socket.h> //socket(), bind()
#include <sys/types.h>  //socket(), bind()
#include <unistd.h>

class client {
private:
  int mySocket;                          // deskryptor gniazda
  struct sockaddr_in destinationAddress; // parametry gniazda
  bool flag;
  enum { p_size = 512 };

public:
  client(int serwer_port);
  ~client();

  int &get_mySocket() { return mySocket; }
  struct sockaddr_in *get_destinationAddress() {
    return &destinationAddress;
  }
  void sending();
  void receive();
};

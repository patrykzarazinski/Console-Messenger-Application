#pragma once

#include <algorithm>
#include <arpa/inet.h> // inet_pton()
#include <cerrno>      //errno
#include <cstdio>      //perror()
#include <cstring>     // memset()
#include <iostream>
#include <netinet/in.h> //sockaddr_in()
#include <string>
#include <sys/socket.h> //socket(), bind()
#include <sys/types.h>  //socket(), bind()
#include <unistd.h>
#include <vector>

class serwer {
private:
  int mySocket, newSocket; // deskryptor gniazda
  struct sockaddr_in serwerAddrress,
      clientAddress; // zasoby gniazda serwera i zasoby gniazda klienta
                     // przychodzacego
  enum {
    BACKLOG = 10,
    p_size = 512
  }; // ilosc dozwolonych polaczen czekajacych w kolejce i inne stałe, MAX
     // narazie nie uzywana
  int yes = 1;  // zmienna wykorzystna w funkcji setsockopt
  int sin_size; // rozmiar struktury sockaddr_in
  std::string buff;
  std::vector<int> arraySocket;

public:
  serwer(int serwer_port);
  ~serwer();

  int &get_mySocket() { return mySocket; }
  int &get_newSocket() { return newSocket; }
  struct sockaddr_in *get_serwerAddrress();
  struct sockaddr_in *get_clientAddress() {
    return &clientAddress;
  }
  int get_BACKLOG() { return BACKLOG; }
  int *get_sin_size() { return &sin_size; }
  int size_buff() { return buff.size(); }
  const char *get_buff() { return buff.c_str(); }
  void reset_buff() { buff.clear(); }
  std::vector<int> &get_arraySocket() { return arraySocket; }
  int receive();
  void broadcast(int activeSocket, std::string text);
};

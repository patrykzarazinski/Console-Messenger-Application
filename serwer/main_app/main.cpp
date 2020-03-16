#include "server.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <thread>
#include <unistd.h>

int main(int argc, char *argv[]) {
  serwer serwerObject(5000);

  if (bind(serwerObject.get_mySocket(),
           reinterpret_cast<struct sockaddr *>(
               serwerObject.get_serwerAddrress()),
           sizeof(struct sockaddr)) == -1) {
    exit(3);
    perror("Error function bind");
  }

  if (listen(serwerObject.get_mySocket(), serwerObject.get_BACKLOG()) == -1) {
    perror("Error function listen");
    exit(5);
  }
  serwerObject.get_arraySocket().push_back(serwerObject.get_mySocket());
  while (true) {
    *serwerObject.get_sin_size() = sizeof(struct sockaddr_in);
    if ((serwerObject.get_newSocket() = accept(
             serwerObject.get_mySocket(),
             reinterpret_cast<struct sockaddr *>(
                 serwerObject.get_clientAddress()),
             reinterpret_cast<socklen_t *>(serwerObject.get_sin_size()))) ==
        -1) {
      perror("Error function accept");
      exit(6);
    }

    std::cout << "User connected to server!" << std::endl;
    std::cout << "Got connection from: "
              << inet_ntoa(serwerObject.get_clientAddress()->sin_addr)
              << std::endl;

    serwerObject.get_arraySocket().push_back(
        serwerObject.get_newSocket()); // dodaje nowe gniazdo(socket) do vectora

    std::thread *t1 = new std::thread(&serwer::receive, &serwerObject);
  }

  return 0;
}

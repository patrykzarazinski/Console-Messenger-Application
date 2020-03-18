#pragma once

#include <netinet/in.h> //sockaddr_in()
#include <arpa/inet.h> // inet_pton()
#include <cstring> // memset()
#include <iostream>
#include <sys/types.h> //socket(), bind()
#include <sys/socket.h> //socket(), bind()
#include <cstdio> //perror()
#include <cerrno> //errno
#include <string>
#include <vector>
#include <algorithm>
#include <unistd.h>

class Socket
{
    private:

    int mySocket; //deskryptor gniazda
    struct sockaddr_in serwerAddrress, clientAddress; //zasoby gniazda serwera i zasoby gniazda klienta przychodzacego
    enum{BACKLOG = 10}; 
    int yes = 1; // zmienna wykorzystna w funkcji setsockopt
    int sin_size; // rozmiar struktury sockaddr_in

    int s_socket();

    public:

    Socket(char * ip, int port);
    ~Socket();

    int s_accept();
    void s_setsockopt();
    void s_bind();
    void s_listen();
    void s_connect();

    int get_mySocket(){ return mySocket; }
    struct sockaddr_in & get_clientAddress(){ return clientAddress; }
    struct sockaddr_in & get_serwerAddress(){ return serwerAddrress; }
 };
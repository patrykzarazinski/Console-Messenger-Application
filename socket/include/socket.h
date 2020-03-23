#pragma once

#include <netinet/in.h> //sockaddr_in()
#include <arpa/inet.h> // inet_pton()
#include <cstring> 
#include <iostream>
#include <sys/types.h> //socket(), bind()
#include <sys/socket.h> //socket(), bind()
#include <cstdio> //perror()
#include <string>
#include <vector>
#include <algorithm>

using std::ostream;

class Socket
{
    private:

    int mySocket; //deskryptor gniazda
    struct sockaddr_in serwerAddrress, clientAddress; //zasoby gniazda serwera i zasoby gniazda klienta przychodzacego
    enum{BACKLOG = 10, size = 512}; 
    int yes = 1; // zmienna wykorzystna w funkcji setsockopt
    int sin_size; // rozmiar struktury sockaddr_in

    int s_socket();
    void s_setsockopt();
    void s_bind();
    void s_listen();
    void s_connect();

    public:

    Socket(char * ip, int port, int mode); // mode: 1 tworzy obiekt, ktory jest serwerem; 2 tworzy obiekt, ktory jest clientem

    friend ostream & operator<<(ostream & os, const Socket & s); // wypisuje adres clienta
    int receive(std::string & s, int s_socket); // odbiera dane z dowolnego gniazda
    int receive(std::string & s); // odbiera dane
    int operator>>(std::string & s); // wysyla dane
    int s_accept(); 
 };
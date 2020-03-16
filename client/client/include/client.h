#pragma once

#include <netinet/in.h> //sockaddr_in()
#include <arpa/inet.h> // inet_pton()
#include<cstring> // memset()
#include<iostream>
#include <sys/types.h> //socket(), bind()
#include <sys/socket.h> //socket(), bind()
#include<cstdio> //perror()
#include<cerrno> //errno
#include<cstdio>
#include<cstring>
#include <unistd.h>
#include<string>
#include <pthread.h>

class client
{
    private:

    int mySocket; //deskryptor gniazda
    struct sockaddr_in destinationAddress; //parametry gniazda
    bool flag;
    enum{p_size = 512};

    public:

    client(int serwer_port);
    ~client();

    int & get_mySocket(){ return mySocket; }
    struct sockaddr_in * get_destinationAddress(){ return &destinationAddress; }
    void sending();
    void receive();

};

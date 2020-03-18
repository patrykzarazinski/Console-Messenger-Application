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
#include"socket.h"
#include<thread>

class client
{
    private:

    Socket test;
    struct sockaddr_in destinationAddress; //parametry gniazda
    bool flag;
    enum{p_size = 512};
    std::thread t1;
    std::thread * t2;

    void sending();
    void receive();

    public:

    client(int serwer_port);
    ~client();

    void run();

};
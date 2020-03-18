#pragma once

#include "socket.h"
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
#include <thread>

class serwer
{
    private:

    Socket test;
    enum{p_size = 512}; 
    std::vector<int> arraySocket;
    std::thread * t1;

    int receive();
    void broadcast(int activeSocket, std::string text);

    public:

    serwer(char * serwer_ip, int serwer_port);
    ~serwer();

    void run();
};
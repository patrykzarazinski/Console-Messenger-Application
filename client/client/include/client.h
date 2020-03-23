#pragma once

#include "socket.h"
#include <netinet/in.h> //sockaddr_in()
#include <arpa/inet.h> // inet_pton()
#include <cstring> 
#include <iostream>
#include <sys/types.h> //socket(), bind()
#include <sys/socket.h> //socket(), bind()
#include <cstdio> //perror()
#include <cerrno> //errno
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <string>
#include <pthread.h>
#include <thread>
#include <csignal>
#include <fstream>

class client
{
    private:

    Socket test;
    bool flag;
    std::thread t1;
    std::thread t2;

    void sending();
    void receive();
    bool fileReading(std::string & s);

    public:

    client(char * client_ip, int client_port);
    ~client();

    void run();

};
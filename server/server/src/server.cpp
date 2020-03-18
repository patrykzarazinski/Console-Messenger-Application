#include "server.h"

serwer::serwer(char * serwer_ip, int serwer_port):test(serwer_ip, serwer_port)
{
    t1 = nullptr;

    test.s_setsockopt();
    test.s_bind();
    test.s_listen();

    arraySocket.push_back(test.get_mySocket());

    std::cout << "The server has been opened!" << std::endl;
}

serwer::~serwer()
{
    std::cout << "Server has closed!" << std::endl;
}

int serwer::receive()
{
    int tempSocket = arraySocket.back();
    int counter = 1;
    char p[p_size];

       do
       {
           memset(p, '\0', p_size);

           if((counter = recv(tempSocket, p, p_size - 1, 0)) > 0)
           {
               broadcast(tempSocket, p);
           }

       }while(counter != 0);

       arraySocket.erase(std::remove(arraySocket.begin(), arraySocket.end(), tempSocket), arraySocket.end());
       close(tempSocket);
       std::cout << "User disconnect!" << std::endl;
       std::cout << "Waiting for call..." << std::endl;

    return 1;
}

void serwer::broadcast(int activeSocket, std::string text)
{
    for(auto it = arraySocket.begin(); it != arraySocket.end(); it++)
    {;
        if(*it != activeSocket && *it != test.get_mySocket())
        {
            send(*it, text.c_str() , text.size() + 1, 0);
        }
    }
}

void serwer::run()
{
  while(true)
    {
        std::cout << "Waiting for call..." << std::endl;

        arraySocket.push_back(test.s_accept()); // dodaje nowe gniazdo(socket) do vectora

        std::cout <<"User connected to server!" <<  std::endl;
        std::cout << "Got connection from: " << inet_ntoa(test.get_clientAddress().sin_addr) << std::endl;

        t1 =  new std::thread(&serwer::receive, this);
    }
}
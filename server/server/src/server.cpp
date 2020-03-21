#include "server.h"

using std::cout;
using std::endl;

serwer::serwer(char * serwer_ip, int serwer_port):test(serwer_ip, serwer_port)
{
    t1 = nullptr;

    test.s_setsockopt();
    test.s_bind();
    test.s_listen();

    arraySocket.push_back(test.get_mySocket());

    cout << "The server has been opened!" << endl;
}

serwer::~serwer()
{
    cout << "Server has closed!" << endl;
}

int serwer::receive()
{
    int tempSocket = arraySocket.back();
    int counter = 1;
    std::string buff(512,'\0');

      do
      {

        buff.clear();

        if((counter = recv(tempSocket, const_cast<char *>(buff.c_str()), buff.size() - 1, 0)) > 0)
        {
          broadcast(tempSocket, buff.c_str());
        }

      }while(counter != 0);

      arraySocket.erase(std::remove(arraySocket.begin(), arraySocket.end(), tempSocket), arraySocket.end());
      close(tempSocket);
      cout << "User disconnect!" << endl;
      cout << "Waiting for call..." << endl;

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
        cout << "Waiting for call..." << endl;

        arraySocket.push_back(test.s_accept()); // dodaje nowe gniazdo(socket) do vectora

        cout <<"User connected to server!" <<  endl;
        cout << "Got connection from: " << inet_ntoa(test.get_clientAddress().sin_addr) << endl;

        t1 =  new std::thread(&serwer::receive, this);
    }
}
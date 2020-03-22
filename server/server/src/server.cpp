#include "server.h"

using std::cout;
using std::endl;

serwer::serwer(char * serwer_ip, int serwer_port):test(serwer_ip, serwer_port, 1)
{
  cout << "The server has been opened!" << endl;
}

int serwer::receive()
{
  int tempSocket = arraySocket.back();
  std::string buff;

  while(true)
  {
    buff.clear();

    if(test.receive(buff, tempSocket))
    {
      if(!strcmp(buff.c_str(), "end"))
      {
        broadcast(tempSocket, "User disconnected!");
        break;
      }
      broadcast(tempSocket, buff.c_str());
    }
  }

  arraySocket.erase(std::remove(arraySocket.begin(), arraySocket.end(), tempSocket), arraySocket.end());
  close(tempSocket);
  cout << "User disconnect!" << endl;
  cout << "Waiting for call..." << endl;

  return 1;
}

void serwer::broadcast(int activeSocket, std::string text)
{
  for(auto it = arraySocket.begin(); it != arraySocket.end(); it++)
  {
    if(*it != activeSocket)
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
    cout << "Got connection from: " << test << endl;

    t1 = std::thread(&serwer::receive, this); // ten watek po zerwaniu polaczenia przez clienta samoistnie wyjdzie z pętli i się zakonczy
    t1.detach(); // dlatego tez uzywam detach()
  }
}
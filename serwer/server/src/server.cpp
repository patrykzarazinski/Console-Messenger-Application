#include "server.h"

serwer::serwer(int serwer_port)
{
    //deskryptor gniazda zwrocny przez, int socket(int domain, int type, int protocol);
    if((mySocket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error function socket");
        exit(1);
    }

    if (setsockopt(mySocket, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) //fukcja nadpisuje jeszcze nie zwolniony wczesniej uzywany port
    {
        perror("Error function setsockopt");
        exit(2);
    }

    //ustawienie parametrow gniazda(socket)
    serwerAddrress.sin_family = AF_INET;
    serwerAddrress.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY - automatycznie wybiera ip
    serwerAddrress.sin_port = htons(static_cast<uint16_t>(serwer_port)); // host to network byte order
    memset(&(serwerAddrress.sin_zero), '\0', 8);

    sin_size = sizeof(struct sockaddr_in);

    std::cout << "The server has been opened!" << std::endl;
}

serwer::~serwer()
{
    std::cout << "Server has closed!" << std::endl;
}

struct sockaddr_in * serwer::get_serwerAddrress()
{
    return &serwerAddrress;
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
        if(*it != activeSocket && *it != mySocket)
        {
            send(*it, text.c_str() , text.size() + 1, 0);
        }
    }
}

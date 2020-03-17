#include "client.h"

using std::cout;
using std::endl;
using std::cin;

client::client(int serwer_port)
{
    //deskryptor gniazda zwrocny przez, int socket(int domain, int type, int protocol);
    if((mySocket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error function socket");
        exit(1);
    }

    //ustawienie parametrow gniazda(socket)
    destinationAddress.sin_family = AF_INET;
    destinationAddress.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY - automatycznie wybiera ip, zamiast inet_pton(AF_INET, ip, &(serwerAddrres.sin_addr));
    destinationAddress.sin_port = htons(static_cast<uint16_t>(serwer_port)); // host to network byte order
    memset(&(destinationAddress.sin_zero), '\0', 8);

    flag = true;

}

client::~client()
{
    cout << "You disconnected!" << endl;
}

void client::sending()
{
    std::string buff;
    do
    {
        buff.clear();
        getline(cin, buff);
        if(send(mySocket, buff.c_str() , buff.size() + 1, 0) == -1)
        {
            perror("Error function recv");
            exit(7);
        }
    }while(buff != "end");

    flag = false;
}

void client::receive()
{
    char p[p_size];

    while(flag)
    {
        memset(p, '\0', p_size);
        if(recv(mySocket, p, p_size - 1, 0) > 0) //MSG_DONTWAIT
        {
            printf("%s\n", p);
        }
    }
}

#include "socket.h"

using std::cerr;
using std::endl;

Socket::Socket(char * ip, int port)
{ 
	mySocket = s_socket();

    //ustawienie parametrow gniazda(socket)
    serwerAddrress.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &(serwerAddrress.sin_addr));//INADDR_ANY - automatycznie wybiera ip 
    serwerAddrress.sin_port = htons(static_cast<uint16_t>(port)); // host to network byte order
    memset(&(serwerAddrress.sin_zero), '\0', 8);

    sin_size = sizeof(struct sockaddr_in);
}

void Socket::s_bind()
{
	if(bind(mySocket,reinterpret_cast<struct sockaddr*>(&serwerAddrress) , sizeof(struct sockaddr)) == -1)
    {
        cerr << "Error with function bind" << endl;
        exit(3);
    }
}

void Socket::s_listen()
{
	if(listen(mySocket, BACKLOG) == -1)
    {
        cerr << "Error with function listen" << endl;
        exit(5);
    }
}

void Socket::s_setsockopt()
{
	if (setsockopt(mySocket, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) //fukcja nadpisuje jeszcze nie zwolniony wczesniej uzywany port
    {
        cerr << "Error with function setsockopt" << endl;
        exit(2);
    }
}

int Socket::s_socket()
{
	return socket(PF_INET, SOCK_STREAM, 0);
}

int Socket::s_accept()
{
	return accept(mySocket, reinterpret_cast<struct sockaddr *>(&clientAddress), reinterpret_cast<socklen_t *>(&sin_size));
}

void Socket::s_connect()
{
	if(connect(mySocket, reinterpret_cast<struct sockaddr*>(&serwerAddrress) , sizeof(struct sockaddr)) == -1)
    {
        cerr << "Error with function connect" << endl;
        exit(2);
    }
}
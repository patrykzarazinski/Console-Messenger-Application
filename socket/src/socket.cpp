#include "socket.h"

using std::cerr;
using std::endl;
using std::cout;

Socket::Socket(char * ip, int port, int mode)
{ 
	mySocket = s_socket();

    //ustawienie parametrow gniazda(socket)
    serwerAddrress.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &(serwerAddrress.sin_addr));//INADDR_ANY - automatycznie wybiera ip 
    serwerAddrress.sin_port = htons(static_cast<uint16_t>(port)); // host to network byte order
    memset(&(serwerAddrress.sin_zero), '\0', 8);

    sin_size = sizeof(struct sockaddr_in);

    switch(mode)
    {
    	case 1:
	    	s_setsockopt();
	    	s_bind();
	    	s_listen();
    		break;
    	case 2:
    		s_connect();
    		break;
    	default:
    		cout << "You have chosen the wrong mode!" << endl;
    		exit(11);
    }
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

ostream & operator<<(ostream & os, const Socket & s)
{
	os << inet_ntoa(s.clientAddress.sin_addr);
	return os;
}

int Socket::receive(std::string & s, int s_socket)
{
	s = std::string(size, '\0');

	if(recv(s_socket, const_cast<char *>(s.c_str()), s.size() - 1, 0) > 0)
		return 1;

    return -1;
}

int Socket::receive(std::string & s)
{
	s = std::string(size, '\0');

	if(recv(mySocket, const_cast<char *>(s.c_str()), s.size() - 1, 0) > 0)
        return 1;
    
    return -1;
}

int Socket::operator>>(std::string & s)
{
	if(send(mySocket, s.c_str() , s.size() + 1, 0) == -1)
        return -1;

	return 1;
}

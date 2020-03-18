#include "client.h"

using std::cout;
using std::endl;
using std::cin;

client::client(int serwer_port)
{
    t2 = nullptr;
    test.s_connect();

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
        if(send(test.get_mySocket(), buff.c_str() , buff.size() + 1, 0) == -1)
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
        if(recv(test.get_mySocket(), p, p_size - 1, 0) > 0) //MSG_DONTWAIT
        {
            printf("%s\n", p);
        }
    }
}

void client::run()
{
    cout << "You are now connected!" << endl;
    cout << "To disconnect write >> end << !" << endl;

    t1 = std::thread(&client::sending, this);
    t2 = new std::thread(&client::receive, this);

    t1.join();
}
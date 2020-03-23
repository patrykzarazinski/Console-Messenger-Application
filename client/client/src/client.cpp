#include "client.h"

using std::cout;
using std::endl;
using std::cin;
using std::cerr;

client::client(char * client_ip, int client_port):test(client_ip, client_port, 2)
{
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
        test >> buff;
    }while(buff != "end");

    flag = false;
}

void client::receive()
{
    std::string buff;

    while(flag)
    {
        buff.clear();
        if(test.receive(buff))
        {   
            if(flag)
                cout << buff.c_str() << endl;
        }
    }
}

void client::run()
{
    cout << "You are now connected!" << endl;
    cout << "To disconnect write >> end << !" << endl;

    signal(SIGINT, SIG_IGN); // wylacza mozliwosc uzycia ctrl + c

    t1 = std::thread(&client::sending, this);
    t2 = std::thread(&client::receive, this);

    t1.join();
    t2.join();
}

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
        if(buff == "file")
        {
            test >> "file";
            if(!fileReading(buff))
                continue;
            test >> buff;
            cout << "You have send the file!" << endl;
            buff.clear();
            continue;
        }
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
    cout << "To disconnect write >> end << ! To send file write >> file << !" << endl;

    signal(SIGINT, SIG_IGN); // wylacza mozliwosc uzycia ctrl + c

    t1 = std::thread(&client::sending, this);
    t2 = std::thread(&client::receive, this);

    t1.join();
    t2.join();
}

bool client::fileReading(std::string & s)
{
    s.clear();
    std::string temp;
    cout << "Enter the file path!" << endl;
    getline(cin, temp);

    std::ifstream file(temp, std::ios_base::in);
    if(!file.is_open())
    {
        cout << "You have entered the wrong path, press >> enter << to back!" << endl;
        file.clear();
        file.close();
        return false;
    }

    s.clear();
    char ch;
    while(file.get(ch))
        s += ch;

    file.clear();
    file.close();
    return true;
}

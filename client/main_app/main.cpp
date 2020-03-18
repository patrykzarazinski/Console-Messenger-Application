#include <iostream>
#include"client.h"
#include<thread>

using std::cout;
using std::endl;
using std::thread;

int main(int argc, char *argv[])
{
    client clientObject(5000);

    if(connect(clientObject.get_mySocket(), reinterpret_cast<struct sockaddr*>(clientObject.get_destinationAddress()) , sizeof(struct sockaddr)) == -1)
    {
        perror("Error function connect");
        exit(2);
    }

    cout << "You are now connected!" << endl;
    cout << "To disconnect write >> end << !" << endl;

    thread t1(&client::sending, &clientObject);
    thread * t2 = new thread(&client::receive, &clientObject);

    t1.join();
    //t2.join();

    close(clientObject.get_mySocket());

    return 0;
}

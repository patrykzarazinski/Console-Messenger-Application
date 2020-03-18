#include"client.h"
#include <iostream>

int main(int argc, char *argv[])
{
    client clientObject(5000);

    clientObject.run();

    return 0;
}
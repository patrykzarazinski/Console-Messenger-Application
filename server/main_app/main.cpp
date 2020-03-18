#include"server.h"
#include <iostream>

int main(int argc, char *argv[])
{
    serwer serwerObject(5000);

    serwerObject.run();

    return 0;
}
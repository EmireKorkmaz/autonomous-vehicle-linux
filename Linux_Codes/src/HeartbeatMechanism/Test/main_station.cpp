#include "heartbeatsMechanism.h"
#include <iostream>
#include <thread>
#include <unistd.h>
//This function will be called from a thread

int main()
{
    HeartbeatsMechanism smy("127.0.0.1", 2564, 2563, false);
    sleep(1000);

    return 0;
}
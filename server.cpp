#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <vector>
#include "./include/Util.h"
#include "Epoll.h"
#include "./include/Socket.h"
#include "./include/Channel.h"
#include"../include/EventLoop.h"
#include"../include/Server.h"
int main() {
    EventLoop*loop = new EventLoop;
    Server* server = new Server(loop);
    loop->loop();
    return 0;
}


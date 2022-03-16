#pragma once
#include<sys/epoll.h>
#include<vector>
#include<unistd.h>
#include<string.h>

#include"./Util.h"

#define MAXEVENTS 100
class Channel;
class Epoll{
    int epfd;
    struct epoll_event* events;
    public:
    Epoll();
    ~Epoll();
    void addFd(int fd, uint32_t op);
    std::vector<Channel*> poll(int time_out);
    void update_channel(Channel* ch);
};
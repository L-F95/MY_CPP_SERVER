#pragma once
#include<sys/epoll.h>
#include<functional>
#include"./Eventloop.h"
class Epoll;

class Channel{
    private:
    Epoll* ep;
    int fd;
    uint32_t events;
    uint32_t revents;
    bool inEpoll;
    EventLoop* loop;
    std::function<void()> callback;
    public:
    Channel(EventLoop* el, int fd);
    ~Channel();

    void enableReading();
    int getFd();
    uint32_t getEvents();
    uint32_t getRevents();
    bool getInEpoll();
    void setInEpoll();

    void setRevents(uint32_t);

    // day - 2
    void handleEvent();
    void setCallback(std::function<void()>);

};
#pragma once
#include"./Epoll.h"
#include<functional>
class EventLoop;
class Channel{
    int fd;
    EventLoop* loop;
    uint32_t events;
    uint32_t revents;
    bool inepoll;
    std::function<void()> callback;
    public:
    Channel(int,EventLoop* );
    ~Channel();
    void enable_reading();
    int get_fd();
    uint32_t get_events();
    uint32_t get_revents();
    bool inEpoll();
    void set_inEpoll();
    void set_revent(uint32_t);
    void set_event(uint32_t ev);

    void setCallback(std::function<void()>);
    void handleReadEvent();
};
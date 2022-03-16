#include "../include/Channel.h"
#include"../include/EventLoop.h"
Channel::Channel(int _fd, EventLoop* _loop){
    fd = _fd;
    loop = _loop;
    inepoll = false;
    events = 0;
    revents = 0;
}
Channel::~Channel(){}
void Channel::enable_reading(){
    events  = EPOLLIN| EPOLLET;
    loop->update_channel(this);
}

int Channel::get_fd(){
    return fd;
}
uint32_t Channel::get_events(){
    return events;
}
uint32_t Channel::get_revents(){
    return revents;
}
bool Channel::inEpoll(){
    return inepoll;
}

void Channel::set_inEpoll(){
    inepoll = true;
}
void Channel::set_event(uint32_t ev){
    events = ev;
}
void Channel::set_revent(uint32_t ev){
    revents = ev;
}
void Channel::setCallback(std::function<void()> cb){
    callback = move(cb);
}

void Channel::handleReadEvent(){
    callback();
}
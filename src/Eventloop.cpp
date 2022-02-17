#include"../include/Eventloop.h"
#include"../include/Epoll.h"
#include"../include/Channel.h"
#include<vector>

EventLoop::EventLoop() : ep(nullptr), quit(false){
    ep = new Epoll();
}

EventLoop::~EventLoop()
{
    delete ep;
}


void EventLoop::loop(){
    while(!quit){
    std::vector<Channel*> chs;
        chs = ep->poll(-1);
        for(auto it = chs.begin(); it != chs.end(); ++it){
            (*it)->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel *ch){
    ep->updateChannel(ch);
}
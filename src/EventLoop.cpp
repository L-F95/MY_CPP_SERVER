#include "../include/EventLoop.h"
#include"../include/Epoll.h"
#include"../include/Channel.h"
#include<vector>

EventLoop::EventLoop():ep(nullptr),quit(false){
    ep = new Epoll();
}

EventLoop::~EventLoop(){
    delete ep;
}

void EventLoop::loop(){
    while(!quit){
        std::vector<Channel*> channels;
        channels = ep->poll(1000);
        for(auto it = channels.begin(); it != channels.end();++it){
            (*it)->handleReadEvent();
        }
    }
}
void EventLoop::update_channel(Channel *ch){
    ep->update_channel(ch);
}
#include"../include/Epoll.h"
#include"../include/Channel.h"

Epoll::Epoll(){
    epfd = epoll_create(5);
    ErrorIf(epfd == -1, "Epoll create failed");
    events = new epoll_event[MAXEVENTS];
    bzero(events, sizeof(epoll_event)*MAXEVENTS);
}

Epoll::~Epoll(){
    if(epfd != -1){
        close(epfd);
        epfd = -1;
    }
    delete []events;
}

void Epoll::addFd(int fd, uint32_t ev){
    epoll_event event;
    event.data.fd = fd;
    event.events = ev;
    ErrorIf( epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event)== -1, "epoll_ctl_add failed");
}

std::vector<Channel*> Epoll::poll(int timeout){
    std::vector<Channel*> active_Channels;
    int nread = epoll_wait(epfd, events,MAXEVENTS,timeout);
    ErrorIf(nread == -1, "epoll_wait error\n"); 
    for(int i = 0;i<nread;i++){
        Channel* ch = (Channel*)events[i].data.ptr;
        ch->set_revent(events[i].events);
        active_Channels.push_back(ch);
    }
    return active_Channels;
}

void Epoll::update_channel(Channel* ch){
    epoll_event ev;
    bzero(&ev,sizeof(ev));
    ev.data.ptr = ch;
    ev.events = ch->get_events();
    if(ch->inEpoll()){
        ErrorIf(epoll_ctl(epfd, EPOLL_CTL_MOD,ch->get_fd(),&ev)== -1,"Add channel error\n");
    }else{
        ErrorIf(epoll_ctl(epfd, EPOLL_CTL_ADD,ch->get_fd(),&ev)== -1,"Add channel error\n");
        ch->set_inEpoll();
    }
    
}
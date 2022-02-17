#include"../include/Socket.h"
#include "../include/util.h"
#include<sys/socket.h>
#include<fcntl.h>
#include<unistd.h>
Socket::Socket(){
    fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(fd == -1, "socket error");
}

Socket::Socket(int lfd):fd(lfd){
    errif(fd == -1, "socket error");    
}

Socket::~Socket(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}

void Socket::Bind(InetAddress* IA){
    errif(bind(fd, (struct sockaddr*)&IA->addr, IA->addr_len)==-1,"bind error");
}

void Socket::Listen(){
    errif(listen(fd, 5)==-1, "listen error");
}
void Socket::setnonblocking(){
    fcntl(fd, F_SETFL, fcntl(fd,F_GETFL) |O_NONBLOCK);
}

int Socket::Accept(InetAddress* IA){
    int cfd = accept(fd,(sockaddr*)&IA->addr,&IA->addr_len);
    errif(cfd == -1, "accept() failed");
    return cfd;
}
int Socket::getFd(){
    return fd;
}
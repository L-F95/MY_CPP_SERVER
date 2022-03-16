#include "../include/Socket.h"

InetAddress::InetAddress():addrlen(sizeof(addr)){
    bzero(&addr, addrlen);
}
InetAddress::~InetAddress(){}
InetAddress::InetAddress( const char* ip,uint16_t port ){
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    addrlen = sizeof(addr);
}

Socket::Socket():fd(-1){
    fd = socket(AF_INET, SOCK_STREAM, 0);
    ErrorIf(fd == 1, "create socket failed\n");
}
Socket::Socket( int _fd):fd(_fd){
    ErrorIf(fd == -1,"Socket error\n");
    
}
// 当sokcet 关闭时 将 fd 置为-1
Socket::~Socket(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}

void Socket::Bind(InetAddress* IA){
  ErrorIf(bind(fd,(sockaddr*)(&IA->addr),IA->addrlen)!= 0,"bind failed\n");

}

int Socket::Accept(InetAddress* IA){
    int clnt_sockfd = ::accept(fd,(sockaddr*)(&IA->addr),&IA->addrlen);
    
    ErrorIf(clnt_sockfd == -1, "accept() failed");
    return clnt_sockfd;
}

int Socket::get_fd(){
    return fd;
}
// 设置描述符为非阻塞
void Socket::setnoBlock(){
    fcntl(fd,F_SETFL,fcntl(fd, F_GETFL)|O_NONBLOCK);
}

void Socket::Listen(int backlog){
    ErrorIf(listen(fd, backlog) == -1,"listen failed\n");
}
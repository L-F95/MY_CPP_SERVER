#include <functional>
#include <string.h>
#include <unistd.h>

#include"../include/Server.h"
#include "../include/Socket.h"
#include "../include/Channel.h"
#include"../include/Acceptor.h"
#define  MAX_BUF 1024
Server::Server(EventLoop*_loop):loop(_loop){
    acceptor = new Acceptor(loop);
    
    std::function<void(Socket*)> cb = std::bind(&Server::newConnection, this,std::placeholders::_1);
    acceptor->set_new_connection_cb(cb);
}

Server::~Server(){}

void Server::handleReadEvent(int fd){
    char buf[MAX_BUF];
    while(true){
        int n = read(fd, buf, sizeof(buf));
        if(n  == -1 && errno == EINTR){
            printf("continue read\n");
            continue;
        }else if( n==-1 &&(errno == EAGAIN || errno == EWOULDBLOCK)){
            printf("data read once\n");
            break;
        }else if(n == 0){
            printf("client disconnected\n");
            close(fd);
            break;
        }else if(n == -1){
            printf("read error\n");
            close(fd);
            break;
        }else if(n>0){
            printf("message from client: %s\n",buf);
            write(fd,buf,sizeof(buf));
        }
    }
}

void Server::newConnection(Socket *serv_sock){
    InetAddress *clnt_addr = new InetAddress;
    Socket* clnt_sock = new Socket(serv_sock->Accept(clnt_addr));
    printf("new connect fd；%d,IP:%s Port:%d\n",
        clnt_sock->get_fd(),inet_ntoa(clnt_addr->addr.sin_addr),htons(clnt_addr->addr.sin_port)
    );
    clnt_sock->setnoBlock();
    Channel * clnt_ch = new Channel(clnt_sock->get_fd(),loop);
    std::function<void()>cb  = std::bind(&Server::handleReadEvent, this,clnt_sock->get_fd());
    clnt_ch->setCallback(cb);
    clnt_ch->enable_reading();
}


#include "../include/Acceptor.h"
#include "../include/EventLoop.h"
#include "../include/Channel.h"
#include"../include/Socket.h"
Acceptor::Acceptor(EventLoop*_loop):loop(_loop){
    sock = new Socket();
    IA =  new InetAddress("127.0.0.1",8888);
    sock->Bind(IA);
    sock->setnoBlock();
    sock->Listen(5);
    ch = new Channel(sock->get_fd(), loop);
    std::function<void()> cb = std::bind(&Acceptor::accept_connections, this);
    ch->setCallback(cb);
    ch->enable_reading();
}
Acceptor::~Acceptor(){
    delete sock;
    delete IA;
    delete ch;
}
void Acceptor::accept_connections(){
    new_connection_cb(sock);
}
void Acceptor::set_new_connection_cb(std::function<void(Socket *)> cb){
    new_connection_cb = cb;
}
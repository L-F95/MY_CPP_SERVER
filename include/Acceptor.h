#pragma once
#include<functional>
class EventLoop;
class Socket;
class InetAddress;
class Channel;
class Acceptor{
    EventLoop * loop;
    Socket * sock;
    InetAddress* IA;
    Channel* ch;
    public:
    Acceptor(EventLoop * loop);
    ~Acceptor();
    void accept_connections();
    std::function<void(Socket *)> new_connection_cb;
    void set_new_connection_cb(std::function<void(Socket *)> cb);
};
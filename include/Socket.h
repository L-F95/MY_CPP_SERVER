#pragma once
#include"./InetAddress.h"
class InetAddress;
class Socket
{
private:
    int fd;
public:
    Socket();
    Socket(int);
    ~Socket();

    void Bind(InetAddress*);
    void Listen();
    void setnonblocking();

    int Accept(InetAddress*);

    int getFd();
};


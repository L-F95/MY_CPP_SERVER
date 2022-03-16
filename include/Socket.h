#include <sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"./Util.h"
#include<sys/unistd.h>
#include<string.h>
#include<fcntl.h>
// 提供一个 ip 和 地址结构体的转换
class InetAddress{
    public:
    sockaddr_in addr;
    socklen_t addrlen;
    InetAddress();
    InetAddress(const char * ip, uint16_t port);
    ~InetAddress();
};
class Socket{
    int fd;

    public:
    Socket();
    Socket(int _fd);

    ~Socket();
    void Bind(InetAddress*);
    int  Accept(InetAddress*);
    void Listen(int backlog);
    void setnoBlock();
    int get_fd();
};
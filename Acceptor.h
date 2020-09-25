#ifndef Acceptor_1
#define Acceptor_1
#include"tcp.h"
#include"Channel.h"
#include<sys/epoll.h>
#include<vector>
class Eventloop;
struct client_info{
    sockaddr_in client_addr;
    socklen_t addr_len;
    int cld;

};
//建立一个本地socket接受客户端的连接
class Acceptor
{
private:
    Eventloop* loop;
    int socketfd;
    Channel AcceptChannel;
    std::vector<Channel> Clientchannel;
    // std::vector<epoll_event> Clientevent;
    struct epoll_event event;//传递给loop中的epoll函数
    client_info client_;//接受客户信息
public:
    Acceptor(Eventloop* loop);
    void Listen();
    void add_toloop();
    void HandleRead();
    void newconnection(int client);
    int socket_fd(){return socketfd;}
    void test_readcallback();
    void test_writecallback();
    ~Acceptor();
};




#endif
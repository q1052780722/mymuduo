#ifndef eventloop
#define eventloop
#include<pthread.h>
#include"Channel.h"
#include"Acceptor.h"
#include<map>
#include<vector>
struct epoll_event;
class Eventloop
{
private:
    pthread_t tid;
    std::vector<epoll_event>add_list;//记录加入到epoll中的fd 用于test
    Acceptor acceptor;
    epoll_event activelist[20];//接受epoll返回的活动服务器
    std::map<int,Channel*>Channellist;//int fd,fd对应的处理函数
    int epoll_handle;
public:
    Eventloop();
    void loop();
    void add_Acceptor_data();

    void assert_loopinthisthread();
    void update_Channel(Channel* channel);
    void add_epoll_handle(int fd,epoll_event* event);
    void del_epoll_handle(int fd ,epoll_event* event);

    void add_add_list(epoll_event x){add_list.push_back(x);}
    void travel_add_list();

    // void ReadCallback(int clientfd);
    // void Writecallback(int clientfd);
    ~Eventloop();
};



#endif
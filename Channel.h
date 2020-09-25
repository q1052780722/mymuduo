#ifndef Channel_1
#define Channel_1
#include<boost/function.hpp>
#include<sys/epoll.h>
class Eventloop;
struct epoll_event;
//Channel class:文件描述符与他的处理函数的集合
class Channel
{ 

    typedef boost::function<void()>Callback;
    // typedef boost::function<void(int)>EcoCallback;
private:
    Eventloop* loop;
    int fd_;
    struct epoll_event event;
    
    Callback ReadCallback;
    Callback WriteCallback;
    Callback ErroCallback;
public:
    // EcoCallback Ecocallback;
    Channel(Eventloop*loop,int fd);
    // void set_EcoCallback(const EcoCallback &cb){Ecocallback=cb;}
    void set_ReadCallback(const Callback &cb){ReadCallback=cb;}
    void set_WriteCallback(const Callback &cb){WriteCallback=cb;}
    void set_ErroCallback(const Callback &cb){ErroCallback=cb;}
    // void DoEcoCallback(){if(Ecocallback) Ecocallback(int);}
    void DoReadCallback(){if(ReadCallback) ReadCallback();}
    void DoWriteCallback(){if(WriteCallback) WriteCallback();}
    void DoErroCallback(){if(ErroCallback) ErroCallback();}
    void enable_read(){event.events|=EPOLLIN;}
    void enable_write(){event.events|=EPOLLOUT;}

    int fd(){return fd_;}
    ~Channel();
};






#endif
#include"Channel.h"
#include<iostream>
#include<sys/epoll.h>
using namespace std;

Channel::Channel(Eventloop* loop,int fd)
:loop(loop),
 fd_(fd)
 
{
    event.data.fd=fd;
}

Channel::~Channel(){
    
}
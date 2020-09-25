#include"Eventloop.h"

#include<unistd.h>
#include<iostream>
#include<boost/utility.hpp>
#include<pthread.h>
#include<syscall.h>
#include<assert.h>
#include<sys/epoll.h>
#include<boost/bind.hpp>
using namespace std;

__thread Eventloop* thisloop=NULL;

Eventloop::Eventloop()
:tid(syscall(SYS_gettid)),
 acceptor(this)
{
    epoll_handle=epoll_create(20);
      if(thisloop==NULL){
          thisloop=this;
      }
      else cout<<"thread has extern Eventloop,bind loop erro"<<endl;

}
//将Acceptor中的socket 加入监听列表 便于接受客户端连接
void Eventloop::add_Acceptor_data(){
    acceptor.add_toloop();
}
void Eventloop::loop(){
    assert_loopinthisthread();
    //暂时用于测试 FIX:epoll
    while(1){
    int client_size=epoll_wait(epoll_handle,activelist,20,0);
   cout<<"client_size:"<<client_size<<endl;
   sleep(2);
        
        for(int i=0;i<client_size;i++){
            if(activelist[i].data.fd==acceptor.socket_fd()){
                //有客户端接入
                Channellist[acceptor.socket_fd()]->DoReadCallback(); 
            }
            else{
                //客户端可读或可写
               
                if(activelist[i].events&EPOLLIN){
                     cout<<"client: in"<<endl;
                     char buff[64];
                     int n=read(activelist[i].data.fd,buff,sizeof(buff));
                     if(n==0){
                         cout<<"read 0 bytes should shutdowm"<<endl;
                        //FIX remove activelist[i]
                     }
                     else{
                         write(activelist[i].data.fd,buff,n);
                     }
                    //  ReadCallback(activelist[i].data.fd);
                    //  Channellist[activelist[i].data.fd]->ReadCallback();
                    //测试统一ReadCallback              
                    // ReadCallback(activelist[i].data.fd);
                    // Channellist[activelist[i].data.fd]->set_ReadCallback(boost::bind(&Eventloop::ReadCallback,this));
                    // Channellist[activelist[i].data.fd]->set_EcoCallback(boost::bind(&Eventloop::ReadCallback,this,_1));
                    // Channellist[activelist[i].data.fd]->Ecocallback(activelist[i].data.fd);
                     Channellist[activelist[i].data.fd]->DoReadCallback();
                }
                if(activelist[i].events&EPOLLOUT){
                       cout<<"client: out"<<endl;
                       cout<<"channelist:size:"<<Channellist.size()<<endl;
                 
                Channellist[activelist[i].data.fd]->DoWriteCallback();
                }
                if(activelist[i].events&EPOLLERR){
                       cout<<"client: err"<<endl;
                    Channellist[activelist[i].data.fd]->DoErroCallback();
                }
                if(activelist[i].events&EPOLLHUP){
                     cout<<"client hup"<<endl;
                }
            }
        }
    }
    
    // travel_add_list();
}
void Eventloop::assert_loopinthisthread(){
    // std::cout<<(thisloop==NULL)<<std::endl;
     assert(thisloop==this);
}
void Eventloop::update_Channel(Channel* channel){
    // cout<<channel->fd()<<endl;
    // cout<<"i am alive1"<<endl;
    Channellist[channel->fd()]=channel;
    // cout<<"i am  alive2"<<endl;
}
void Eventloop::add_epoll_handle(int fd ,epoll_event* event){
    epoll_ctl(epoll_handle,EPOLL_CTL_ADD,fd,event);
}
void Eventloop::del_epoll_handle(int fd ,epoll_event* event){
    epoll_ctl(epoll_handle,EPOLL_CTL_DEL,fd,event);
}
void Eventloop::travel_add_list(){
    for(int i=0;i<add_list.size();i++){
        cout<<"add_list["<<i<<"]"<<add_list[i].data.fd<<endl;
    }
}



Eventloop::~Eventloop(){
    thisloop=NULL;
}

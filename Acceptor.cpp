#include<unistd.h>
#include<iostream>
#include"Acceptor.h"
#include"Eventloop.h"
#include"InetAddress.h"
#include<sys/epoll.h>
// #include"tcp.h"
#include<boost/bind.hpp>
using namespace std;

Acceptor::Acceptor(Eventloop* loop)
:loop(loop),
socketfd(bind_addr("127.0.0.1",7777)),
AcceptChannel(loop,socketfd)
{ //完成套接字创建 
    Listen();
    AcceptChannel.enable_read();
    AcceptChannel.set_ReadCallback(boost::bind(&Acceptor::HandleRead,this));
    //
 
    event.events=EPOLLIN;
    event.data.fd=socketfd;
    
   
    
}
void Acceptor::add_toloop(){
     loop->add_epoll_handle(socketfd,&event);
    loop->add_add_list(event);
      loop->update_Channel(&AcceptChannel);
}
void Acceptor::Listen(){
     int erro=::listen(socketfd,20);
    if(erro==0)
        std::cout<<"listen ok"<<std::endl;
    else
        std::cout<<"listen erro"<<std::endl;

}

void Acceptor::HandleRead(){
    loop->assert_loopinthisthread();
    bzero(&client_,sizeof(client_));
    int connfd=accept(socketfd,(sockaddr*)&client_.client_addr,&client_.addr_len);
        // if(num==-1) perror("accept erro\n");

        if(connfd>=0){
            //接受了客户的地址以及套接字connfd
            // cout<<"i get client"<<endl;
            static InetAddress addr(client_.client_addr);
            newconnection(connfd);
            // if(newConnectionCallback){newConnectionCallback(connfd,addr);}
            //FIX 加入epoll中(fd,event) 
            //loop->add_epoll_handle(); 
        }
        else {

            std::cout<<"handle read close it"<<std::endl;
            close(socketfd);
        }
}

void Acceptor::newconnection(int client){
    //new event
    epoll_event event;
    event.data.fd=client;
    event.events|=EPOLLIN;
    event.events|=EPOLLOUT;
    // Clientevent.push_back(event);
    //new channel
    Channel channel(loop,client);
//     cout<<"i am alive1"<<endl;
     channel.set_ReadCallback(boost::bind(&Acceptor::test_readcallback,this));
     channel.set_WriteCallback(boost::bind(&Acceptor::test_writecallback,this));
    //  cout<<"i am alive2"<<endl;
    Clientchannel.push_back(channel);
    // channel.DoReadCallback();
    loop->add_epoll_handle(client,&event);
    // cout<<"iam alive3"<<endl;
    loop->update_Channel(&Clientchannel[Clientchannel.size()-1]);
    // cout<<"i am alive4"<<endl;
}
void Acceptor::test_readcallback(){
    cout<<"i am read callback"<<endl;
}
void Acceptor::test_writecallback(){
    cout<<"i am write callbanc"<<endl;
}
Acceptor::~Acceptor(){

}
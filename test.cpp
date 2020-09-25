#include<iostream>
#include<sys/epoll.h>
#include<sys/socket.h>
#include"../tcp-model/tcp.h"
#include"../mymuduo/InetAddress.h"
#include<sys/poll.h>
using namespace std;
int main(){
   int handle=epoll_create(10);
   int socketfd=socket(AF_INET,SOCK_STREAM,0);
    
    client_info clients;
    InetAddress adr("127.0.0.1",7777);
    int sfd=bind_addr(adr.ip,adr.port);
    listen(sfd,10);


    struct epoll_event event;
    
    event.events=EPOLLIN|EPOLLHUP|EPOLLOUT;
    // event.data.fd=sfd;  
    int max; 
    // struct pollfd pfds[3];
    // pfds[0].fd=sfd;
    // pfds[0].events=POLLIN|POLLOUT;
    // max=poll(pfds,1,-1);
    struct epoll_event revent[10];
    epoll_ctl(handle,EPOLL_CTL_ADD,sfd,&event);  
    max=epoll_wait(handle,revent,10,-1);
    
    clients=my_accept(sfd);
  
   
  
    // cout<<"hello world"<<endl;
    cout<<max<<endl;
    for(int i=0;i<max;i++){
        if(revent->data.fd==sfd){
        cout<<"i get return fd";
        cout<<revent->events<<endl;
        }
            // if(pfds->revents&POLLIN) cout<<"read"<<endl;
        // if(pfds->revents&POLLOUT) cout<<"write"<<endl;
        // cout<<pfds[max].revents<<endl;
    }
    while(1);
  
    return 0;
}
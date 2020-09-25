#ifndef TCP_h
#define TCP_h
#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include"tcp.h"
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

struct client_info{
    sockaddr_in client_addr;
    socklen_t addr_len;
    int cld;

};

struct client_info client;//全局变量客户信息

//输入ip,端口号,返回以绑定的sockfd
inline int bind_addr(const char* ip,int port){
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
        if(socketfd==-1) 
        {
            perror("socket erro\n");
            exit(0);
        }
    //初始化地址
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    inet_pton(AF_INET,&(*ip),(void*)(&addr.sin_addr.s_addr));

    int erro=bind(socketfd,(sockaddr*)&addr,sizeof(addr));
        if(erro==-1)
        {
            perror("bind erro\n");
            exit(0);
        }
    return socketfd;
}
//输入客户端多socket套接字fd 返回客户端的地址.客户端套接字
inline struct client_info& my_accept(int serveSocket_fd){
    
    int cld=accept(serveSocket_fd,(sockaddr*)&client.client_addr,&client.addr_len);
        if(cld==-1) perror("accept erro\n");
        else client.cld=cld;
    return client;

}
//输入ip port返回一个连接(connect)好的socket
inline int my_connect(const char *ip,int port){
    struct sockaddr_in sockaddr;
     //初始化地址
    sockaddr.sin_family=AF_INET;
    sockaddr.sin_port=htons(port);
    inet_pton(AF_INET,&(*ip),(void*)(&sockaddr.sin_addr.s_addr));

    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        perror("socket erro");
        exit(0);
    }

    socklen_t len=sizeof(sockaddr);
    int erro=connect(sockfd,(struct sockaddr*)&sockaddr,len);
    if(erro==-1){
        perror("connect erro");
        exit(0);
    }
    return sockfd;
}
#endif

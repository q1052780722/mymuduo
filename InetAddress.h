#ifndef InetAddress_Y1
#define InetAddress_Y1
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<malloc.h>

/*
 用于ip 端口转换
 将"192.162.1.1"->sin_addr
    port: 8888  ->sin_port
    转换为socket可用的格式
*/
class InetAddress{
public:

InetAddress(char* ip,int port)
:ip(ip),
 port(port)
{
inet_pton(AF_INET,&(*ip),(void*)(&socketaddr.sin_addr.s_addr));
socketaddr.sin_port=htons(port);

}

InetAddress(sockaddr_in sockaddr){
    this->socketaddr=sockaddr;
    port=ntohs(sockaddr.sin_port);
   
	ip=inet_ntoa(sockaddr.sin_addr);

}
    char* ip;
    int port;
    sockaddr_in socketaddr;
};


#endif

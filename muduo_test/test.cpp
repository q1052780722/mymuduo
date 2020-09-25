#include<iostream>
#include<unistd.h>
#include"../Eventloop.h"
#include"../tcp.h"
using namespace std;
int main(){
    Eventloop loop;
    loop.assert_loopinthisthread();
    // loop.travel_add_list();
    // Channel channel(&loop,10);
    loop.add_Acceptor_data();
    loop.loop();
    cout<<"i am ok"<<endl;
    // Eventloop loop2;
    // loop2.assert_loopinthisthread();
    // cout<<"hello world"<<endl;
    return 0;
}

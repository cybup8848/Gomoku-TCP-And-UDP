#ifndef _TCP_SOCKET_H_
#define _TCP_SOCKET_H_
#include<iostream>
//#include <Ws2tcpip.h>//使用新函数inet_pton()，头文件
#include<cstring>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")


#define PORT 8888
#define err(msg) std::cout<<"[error] "<<msg<<" failed.code:"<<WSAGetLastError()<<" File:"<<__FILE__<<" line:"<<__LINE__<<std::endl

bool initWSA();//初始化网络库

SOCKET createServerSocket();//创建服务端socket

SOCKET createClientSocket(const char *ip);//创建客户端socket

bool closeWSA();//关闭网络库

#endif




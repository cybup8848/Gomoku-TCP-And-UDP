#ifndef _UDP_SOCKET_H_
#define _UDP_SOCKET_H_
#include<iostream>
#include<cstring>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

#define err(msg) std::cout<<"[error] "<<msg<<"failed.Code:"<<WSAGetLastError()<<".file:"<<__FILE__<<\
					" line:"<<__LINE__<<std::endl

#define PORT 8888

bool initWSA();

SOCKET createServerSocket();

SOCKET createClientSocket();

bool closeWSA();


#endif






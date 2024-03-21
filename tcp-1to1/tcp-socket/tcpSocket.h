#ifndef _TCP_SOCKET_H_
#define _TCP_SOCKET_H_
#include<iostream>
//#include <Ws2tcpip.h>//ʹ���º���inet_pton()��ͷ�ļ�
#include<cstring>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")


#define PORT 8888
#define err(msg) std::cout<<"[error] "<<msg<<" failed.code:"<<WSAGetLastError()<<" File:"<<__FILE__<<" line:"<<__LINE__<<std::endl

bool initWSA();//��ʼ�������

SOCKET createServerSocket();//���������socket

SOCKET createClientSocket(const char *ip);//�����ͻ���socket

bool closeWSA();//�ر������

#endif




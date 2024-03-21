#include "tcpSocket.h"

bool initWSA()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		err("WSAstartup");
		return false;
	}
	return true;
}

SOCKET createServerSocket()
{
	//1 创建套接字
	SOCKET fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (fd == INVALID_SOCKET) {
		err("socket");
		return INVALID_SOCKET;
	}

	//2 绑定套接字
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = ADDR_ANY;
	addr.sin_port = htons(PORT);
	if (bind(fd, (const struct sockaddr*)&addr, sizeof(addr)) == INVALID_SOCKET) {
		err("bind");
		return INVALID_SOCKET;
	}

	//3 监听
	listen(fd,10);

	return fd;
}

SOCKET createClientSocket(const char* ip)
{
	//1 创建套接字
	SOCKET fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (fd == INVALID_SOCKET) {
		err("scoket");
		return INVALID_SOCKET;
	}

	//2 连接、绑定服务端ip、port
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr=inet_addr(ip);
	//inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr.S_un.S_addr);
	addr.sin_port = htons(PORT);

	if (connect(fd, (const sockaddr*)&addr, sizeof(addr)) == INVALID_SOCKET) {
		err("connect");
		return INVALID_SOCKET;
	}
	return fd;
}

bool closeWSA()
{
	if (WSACleanup() != 0) {
		err("WSACleanup");
		return false;
	}
	return true;
}

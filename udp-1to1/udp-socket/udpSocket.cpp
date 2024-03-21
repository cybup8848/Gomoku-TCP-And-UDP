#include"udpSocket.h"

bool initWSA() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		err("WSAStartup");
		return false;
	}
	return true;
}

SOCKET createServerSocket() {
	//1 创建套接字
	SOCKET fd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (fd == INVALID_SOCKET) {
		err(socket);
		return INVALID_SOCKET;
	}

	//2 绑定套接字
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = ADDR_ANY;
	addr.sin_port = htons(PORT);
	//addr.sin_port = htons(8000);

	if (bind(fd, (const sockaddr*) & addr, sizeof(addr)) == INVALID_SOCKET) {
		err("bind");
		return INVALID_SOCKET;
	}
	return fd;
}

SOCKET createClientSocket() {
	SOCKET fd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (fd == INVALID_SOCKET) {
		err("socket");
	}
	return fd;
}


bool closeWSA() {
	if (WSACleanup() != 0) {
		err("WSACleanup");
		return false;
	}
	return true;
}




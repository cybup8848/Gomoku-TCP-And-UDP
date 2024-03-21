#pragma once
#include"../udp-socket/udpSocket.h"
#include <Ws2tcpip.h>
#include"../udp-common-fun/common_func.h"
bool responseClient(char chs[][N], int coord[], const SOCKET& serverFd, const struct sockaddr_in& clientAddr);
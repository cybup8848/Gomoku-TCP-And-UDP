#include"../tcp-socket/tcpSocket.h"
#include"../tcp-common-fun/common_func.h"
int main(int argc, char* argv[]) {
	initWSA();

	SOCKET clientFd = createClientSocket("127.0.0.1");
	if (clientFd == INVALID_SOCKET) {
		std::cout << "client socket create failed." << std::endl;
		return -1;
	}
	std::cout << "client socket create and connect server successfully " << std::endl;

	char chs[N][N] = {0};
	initChessBoard(chs);
	int coord[2] = {0};
	Result res = Result::OTHER;

	
	for (;;) {
		for (;;) {
			std::cout << "please client to play chess:" << std::endl;
			std::cin >> coord[0] >> coord[1];
			if (coord[0] < 1 || coord[0] >= N || coord[1] < 1 || coord[1] >= N) {
				std::cout << "out of range" << std::endl;
				continue;
			}
			if (chs[coord[0]][coord[1]] != '-') {
				std::cout << "alredy have chess" << std::endl;
				continue;
			}
			break;
		}
		chs[coord[0]][coord[1]] = 'o';
		showChessBoard(chs);
		if (checkWin(chs, coord[0], coord[1], 'o')) {
			coord[0] = coord[1] = 0;
			send(clientFd,(const char *)coord,sizeof(int)*2,0);
			std::cout << "client win" << std::endl;
			break;
		}
		if (checkChessBoardFull(chs)) {
			coord[0] = 0;
			coord[1] = N;
			send(clientFd, (const char*)coord, sizeof(int) * 2, 0);
			std::cout << "server and client both win" << std::endl;
			break;
		}
		if (send(clientFd, (const char*)coord, sizeof(int) * 2, 0) == SOCKET_ERROR) {
			std::cout << "client send data failed" << std::endl;
			break;
		}


		std::cout << "wait server to play chess" << std::endl;
		int ret = recv(clientFd,(char *)coord,sizeof(int)*2,0);
		if (ret <= 0) {
			std::cout << "server is offline" << std::endl;
			break;
		}
		res = checkCoord(coord);
		if (res == Result::SERVER) {
			std::cout << "server win" << std::endl;
			break;
		}
		if (res == Result::NoBlank) {
			std::cout << "server and client both win" << std::endl;
			break;
		}
		chs[coord[0]][coord[1]] = '*';
		showChessBoard(chs);
	}

	closesocket(clientFd);
	closeWSA();
	return 0;
}











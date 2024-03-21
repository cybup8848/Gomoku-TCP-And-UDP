#include"../tcp-socket/tcpSocket.h"
#include"../tcp-common-fun/common_func.h"

int main(int argc, char* argv[]) {
	initWSA();

	SOCKET serverFd = createServerSocket();
	if (serverFd == INVALID_SOCKET) {
		std::cout << "server socket create failed" << std::endl;
		return -1;
	}
	std::cout << "server socket create successfully." << std::endl;
	
	SOCKET clientFd = accept(serverFd,nullptr,nullptr);//accept client to connect
	if (clientFd == INVALID_SOCKET) {
		std::cout << "server accept failed" << std::endl;
		return -1;
	}

	char chs[N][N] = {0};
	initChessBoard(chs);
	int coord[2] = {0};
	//(0,0):client win
	//(N,N):server win
	//(0,N):chess board donot have blank
	Result res = Result::OTHER;
	for (;;) {
		std::cout << "wait client to play chess" << std::endl;
		int ret=recv(clientFd, (char*)coord, sizeof(int) * 2, 0);
		if (ret <= 0) {
			std::cout << "client is offline." << std::endl;
			break;
		} 
		res = checkCoord(coord);
		if (res == Result::CLIENT) {
			std::cout << "client win" << std::endl;
			break;
		}
		if (res == Result::NoBlank) {
			std::cout << "server and client both win" << std::endl;
			break;
		}	
		chs[coord[0]][coord[1]] = 'o';
		showChessBoard(chs);

		for (;;) {
			std::cout << "please server to play chess:"<<std::endl;
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

		chs[coord[0]][coord[1]] = '*';
		showChessBoard(chs);
		if (checkWin(chs, coord[0], coord[1], '*')) {
			std::cout << "server win!" << std::endl;
			coord[0] = N;
			coord[1] = N;
			send(clientFd,(const char *)coord,sizeof(int)*2,0);
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
			std::cout << "server send failed" << std::endl;
			break;
		}
	}

	closesocket(serverFd);
	closesocket(clientFd);
	closeWSA();
	return 0;
}










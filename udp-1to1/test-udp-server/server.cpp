#include"../udp-socket/udpSocket.h"
#include"../udp-common-fun/common_func.h"

int main(int argc, char* argv[]) {
	//1 ³õÊ¼»¯ÍøÂç¿â
	initWSA();

	//2 °ó¶¨
	SOCKET serverFd = createServerSocket();
	
	struct sockaddr_in clientAddr;
	int nClientAddr = sizeof(clientAddr);

	char chs[N][N] = { 0 };
	initChessBoard(chs);
	int coord[2] = { 0 };
	Result res = Result::OTHER;

	for (;;) {
		std::cout << "wait client to play chess..." << std::endl;
		int ret = recvfrom(serverFd, (char*)coord, sizeof(int) * 2, 0, (sockaddr*)&clientAddr, &nClientAddr);
		if (ret <= 0) {
			std::cout << "client is offline" << std::endl;
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

		generateCoord(chs, coord, "please server to play chess:");
		chs[coord[0]][coord[1]] = '*';
		showChessBoard(chs);
		if (checkWin(chs, coord[0], coord[1], '*')) {
			std::cout << "server win!" << std::endl;
			coord[0] = coord[1] = N;
			sendto(serverFd, (const char*)coord, sizeof(int) * 2, 0, (const sockaddr*)&clientAddr, sizeof(clientAddr));
			break;
		}
		if (checkChessBoardFull(chs)) {
			std::cout << "server and client both win" << std::endl;
			coord[0] = 0;
			coord[1] = N;
			sendto(serverFd, (const char*)coord, sizeof(int) * 2, 0, (const sockaddr*)&clientAddr, sizeof(clientAddr));
			break;
		}
		ret = sendto(serverFd, (const char*)coord, sizeof(int) * 2, 0, (const sockaddr*)&clientAddr, sizeof(clientAddr));
		if (ret == SOCKET_ERROR) {
			std::cout << "server send failed" << std::endl;
			break;
		}
	}

	closesocket(serverFd);
	closeWSA();
	system("pause");
	return 0;
}





















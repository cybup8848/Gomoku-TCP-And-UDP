#include"respone.h"

bool responseClient(char chs[][N], int coord[], const SOCKET& serverFd, const struct sockaddr_in& clientAddr) {
	Result res = Result::OTHER;
	res = checkCoord(coord);
	if (res == Result::CLIENT) {
		std::cout << "client win" << std::endl;
		return true;
	}
	if (res == Result::NoBlank) {
		std::cout << "server and client both win" << std::endl;
		return true;
	}
	chs[coord[0]][coord[1]] = 'o';
	showChessBoard(chs);

	generateCoord(chs,coord,"please server to play chess:");
	chs[coord[0]][coord[1]] = '*';
	showChessBoard(chs);
	if (checkWin(chs, coord[0], coord[1], '*')) {
		std::cout << "server win!" << std::endl;
		coord[0] = coord[1] = N;
		sendto(serverFd, (const char*)coord, sizeof(int) * 2, 0, (const sockaddr*)&clientAddr, sizeof(clientAddr));
		return true;
	}
	if (checkChessBoardFull(chs)) {
		std::cout << "server and client both win" << std::endl;
		coord[0] = 0;
		coord[1] = N;
		sendto(serverFd, (const char*)coord, sizeof(int) * 2, 0, (const sockaddr*)&clientAddr, sizeof(clientAddr));
		return true;
	}
	int ret = sendto(serverFd, (const char*)coord, sizeof(int) * 2, 0, (const sockaddr*)&clientAddr, sizeof(clientAddr));
	if (ret == SOCKET_ERROR) {
		std::cout << "server send failed" << std::endl;
		return true;
	}
	return false;
}
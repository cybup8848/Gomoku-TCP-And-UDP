#include"../udp-socket/udpSocket.h"
#include"../udp-common-fun/common_func.h"

int main(int argc, char* argv[]) {
	//1 初始化网络库
	initWSA();

	//2 申请一个套接字，保存服务器的地址信息
	SOCKET clientFd = createClientSocket();
	std::cout << "client socket create successfull..." << std::endl;

	
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.S_un.S_addr = inet_addr("239.1.100.1");
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(PORT);

	//int nServerAddr = 0;//错误设置
	int nServerAddr = sizeof(serverAddr);//正确设置
	
	
	char chs[N][N] = {0};
	initChessBoard(chs);
	int coord[2] = {0};
	Result res = Result::OTHER;
	for (;;) {
		showChessBoard(chs);
		generateCoord(chs,coord,"please client to play chess : ");
		chs[coord[0]][coord[1]] = 'o';
		showChessBoard(chs);
		if (checkWin(chs, coord[0], coord[1], 'o')) {
			coord[0] = coord[1] = 0;
			sendto(clientFd, (const char*)coord, sizeof(int) * 2, 0,(const sockaddr *)&serverAddr,sizeof(serverAddr));
			std::cout << "client win" << std::endl;
			break;
		}
		if (checkChessBoardFull(chs)) {
			coord[0] = 0;
			coord[1] = N;
			sendto(clientFd, (const char*)coord, sizeof(int) * 2, 0, (const sockaddr*)&serverAddr, sizeof(serverAddr));
			std::cout << "server and client both win" << std::endl;
			break;
		}
		if (sendto(clientFd, (const char*)coord, sizeof(int) * 2, 0, (const sockaddr*)&serverAddr, sizeof(serverAddr))
			== SOCKET_ERROR) {
			std::cout << "client send data failed" << std::endl;
			break;
		}

		std::cout << "wait server to play chess" << std::endl;
		int ret = recvfrom(clientFd, (char*)coord, sizeof(int) * 2, 0, (sockaddr*)&serverAddr, &nServerAddr); 
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
	}
	

	closesocket(clientFd);
	closeWSA();

	system("pause");
	return 0;
}























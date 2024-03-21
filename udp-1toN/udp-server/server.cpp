//注意，这两个函数里边有一个sockaddr结构地址，它是用来保存该数据发送者的信息的。上篇提过，TCP是面向连接的，它在通信之前需要进行三次
// 握手来确定双方是否已经准备好了。因此，双方很清楚数据是从哪里来的。而UDP是面向数据包的，因此就好像寄快递一样，你必须在快递上写一张纸条，
// 上面填好姓名，地址等信息，填好之后，接收者才知道该东西是由谁寄过来的。因此，上面两个函数提供了sockaddr结构的地址，用于保存从哪里发来
// 的和发送到哪里的地址信息。

//也和TCP一样，指定SOCKADDR_IN的地址信息（端口，ip），指定完之后呢，若是客户端，则可以直接就进行通信了，若是服务端，则还需要增加一步bind操作，
//当我们调用bind函数，进行绑定后，服务端就可以和客户端进行通信了。而TCP的服务端还有两个步骤，一个是listen，一个是accept，UDP省略了这两个步骤。

#include"respone.h"
#include<unordered_map>
int main(int argc, char* argv[]) {
	//1 初始化网络库
	initWSA();

	//2 绑定本地ip、port
	SOCKET serverFd = createServerSocket();
	std::cout << "server socket create successfully and wait to connect..." << std::endl;

	//加入多播组
	struct ip_mreq serverMreq;
	serverMreq.imr_multiaddr.S_un.S_addr = inet_addr("239.1.100.1");//IP multicast address of group
	serverMreq.imr_interface.S_un.S_addr = ADDR_ANY;////Local IP address of interface
	setsockopt(serverFd,IPPROTO_IP,IP_ADD_MEMBERSHIP,(const char *)&serverMreq,sizeof(serverMreq));

	struct sockaddr_in clientAddr;
	int nClientAddr = sizeof(clientAddr);

	std::unordered_map<int, int>unmap;
	int coord[2] = {0};
	int cn = 0;
	char** chessBoards[N] = { nullptr };
	do {
		std::cout << "wait client to play chess..." << std::endl;
		int ret = recvfrom(serverFd, (char*)coord, sizeof(int) * 2, 0, (sockaddr*)&clientAddr, &nClientAddr);
		if (ret <= 0) {
			std::cout << "client is offline" << std::endl;
			break;
		}

		int clientPort = ntohs(clientAddr.sin_port);
		if (unmap.find(clientPort) == unmap.end()) {
			unmap.insert(std::make_pair(clientPort,cn));
			chessBoards[cn] = (char **)(new char[N][N]);
			initChessBoard((char(*)[N])chessBoards[cn]);
			cn++;
		}

		auto it = unmap.find(clientPort);
		if (responseClient((char (*)[N])chessBoards[it->second], coord, serverFd, clientAddr)) {	
			delete[] chessBoards[it->second];
			chessBoards[it->second] = nullptr;
			unmap.erase(it);
		}
	} while (!unmap.empty());
	
	for (int i = 0;i < N;i++) {
		if (chessBoards[i] == nullptr) {
			continue;
		}
		delete chessBoards[i];
		chessBoards[i] = nullptr;
	}
	
	setsockopt(serverFd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (const char*)&serverMreq, sizeof(serverMreq));
	closesocket(serverFd);
	closeWSA();
	return 0;
}









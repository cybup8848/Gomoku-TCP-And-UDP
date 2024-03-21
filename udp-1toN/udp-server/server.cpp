//ע�⣬���������������һ��sockaddr�ṹ��ַ������������������ݷ����ߵ���Ϣ�ġ���ƪ�����TCP���������ӵģ�����ͨ��֮ǰ��Ҫ��������
// ������ȷ��˫���Ƿ��Ѿ�׼�����ˡ���ˣ�˫������������Ǵ��������ġ���UDP���������ݰ��ģ���˾ͺ���Ŀ��һ����������ڿ����дһ��ֽ����
// ���������������ַ����Ϣ�����֮�󣬽����߲�֪���ö�������˭�Ĺ����ġ���ˣ��������������ṩ��sockaddr�ṹ�ĵ�ַ�����ڱ�������﷢��
// �ĺͷ��͵�����ĵ�ַ��Ϣ��

//Ҳ��TCPһ����ָ��SOCKADDR_IN�ĵ�ַ��Ϣ���˿ڣ�ip����ָ����֮���أ����ǿͻ��ˣ������ֱ�Ӿͽ���ͨ���ˣ����Ƿ���ˣ�����Ҫ����һ��bind������
//�����ǵ���bind���������а󶨺󣬷���˾Ϳ��ԺͿͻ��˽���ͨ���ˡ���TCP�ķ���˻����������裬һ����listen��һ����accept��UDPʡ�������������衣

#include"respone.h"
#include<unordered_map>
int main(int argc, char* argv[]) {
	//1 ��ʼ�������
	initWSA();

	//2 �󶨱���ip��port
	SOCKET serverFd = createServerSocket();
	std::cout << "server socket create successfully and wait to connect..." << std::endl;

	//����ಥ��
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









#author: cybup8848
#email: chengyb2022@shanghaitech.edu.cn
#platform: windows
#IDE: VS2022

tcp-1to1:
	1. tcp socket
	2. 1 to 1 play chess
	3. (0,0): client win
	   (N,N): server win
	   (0,N): server and client both win

udp-1to1:
	1. like tcp-1to1

udp-1toN:
	1. like tcp-1to1 and udp-1to1
	2. use group multicast
	3. set N=10,so the max number of client is 10










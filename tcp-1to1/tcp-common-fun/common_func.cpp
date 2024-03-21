#include"common_func.h"

bool checkWin(char chs[][N],int row,int col,char chessFlag) {
	int cn = 1;

	//up and down check
	int up = row-1;
	while (up > 0 && chs[up][col] == chessFlag) {
		cn++;
		up--;
	}
	int down = row+1;
	while (down < N && chs[down][col] == chessFlag) {
		cn++;
		down++;
	}
	if (cn > 4) {
		return true;
	}

	cn = 1;
	//left and right check
	int left = col - 1;
	while (left > 0&&chs[row][left]==chessFlag) {
		left--;
		cn++;
	}
	int right = col + 1;
	while (right < N && chs[row][right] == chessFlag) {
		right++;
		cn++;
	}
	if (cn > 4) {
		return true;
	}

	cn = 1;
	//left up and right down check
	up = row - 1;
	left = col - 1;
	while (up > 0 && left > 0 && chs[up][left] == chessFlag) {
		cn++;
		up--;
		left--;
	}
	down = row + 1;
	right = col + 1;
	while (down < N && right < N && chs[down][right] == chessFlag) {
		cn++;
		down++;
		right++;
	}
	if (cn > 4) {
		return true;
	}

	cn = 1;
	//left down and right up check
	down = row + 1;
	left = col - 1;
	while (down < N && left>0 && chs[down][left] == chessFlag) {
		cn++;
		down++;
		left--;
	}
	up = row - 1;
	right = col + 1;
	while (up > 0 && right < N && chs[up][right] == chessFlag) {
		cn++;
		up--;
		right++;
	}
	if (cn > 4) {
		return true;
	}

	return false;
}

bool checkChessBoardFull(char chs[][N]){
	for (int i = 1;i < N;i++) {
		for (int j = 1;j < N;j++) {
			if (chs[i][j] == '-') {
				return false;
			}
		}
	}
	return true;
}

//enum Result {CLIENT,SERVER,NoBlank,OTHER};
Result checkCoord(int coord[]) {
	if (coord[0] == 0 && coord[1] == 0) {
		return Result::CLIENT;
	}
	else if (coord[0] == N && coord[1] == N) {
		return Result::SERVER;
	}
	else if (coord[0] == 0 && coord[1] == N) {
		return Result::NoBlank;
	}
	else {
		return Result::OTHER;
	}
}

void initChessBoard(char chs[][N]) {
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			chs[i][j] = '-';
		}
	}
	for (int i = 0;i < N;i++) {
		chs[0][i] = chs[i][0] = char(i + '0');
	}
}

void showChessBoard(char chs[][N]){
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			std::cout << chs[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


#ifndef _COMMON_FUNC_H_
#define _COMMON_FUNC_H_

#include<iostream>
#define N 10
bool checkWin(char chs[][N], int row, int col, char chessFlag);

bool checkChessBoardFull(char chs[][N]);

//enum Result;
enum Result { CLIENT, SERVER, NoBlank, OTHER };
Result checkCoord(int coord[]);

void initChessBoard(char chs[][N]);

void showChessBoard(char chs[][N]);

#endif







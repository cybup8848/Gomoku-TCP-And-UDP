#ifndef _COMMON_FUNC_H_
#define _COMMON_FUNC_H_
#include<iostream>

#define N 10

void initChessBoard(char chs[][N]);


bool checkChessBoardFull(char chs[][N]);

void showChessBoard(char chs[][N]);

//enum Result;
enum Result { CLIENT, SERVER, NoBlank, OTHER };
Result checkCoord(int coord[]);

bool checkWin(char chs[][N], int row, int col, char chessFlag);

void generateCoord(char chs[][N],int coord[],const char *str);

#endif
















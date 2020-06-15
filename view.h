#pragma once
#include <easyx.h>			// 引用图形库头文件
#include <conio.h>
#include <stdio.h>
void drawCb();//画棋盘
void drawPiece(int y, int x, int key);
void PrintBoard(int Board[][CbIntNum]);
int IsBLANK(MOUSEMSG mouse, int y, int x);

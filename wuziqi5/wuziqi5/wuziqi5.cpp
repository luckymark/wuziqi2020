// wuziqi5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "chessboard.h"
#include "Game.h"

int main()
{
	ChessBoard * board = new ChessBoard();
	initGame(board);
	gaming(board);

	delete board;
	closegraph();

    return 0;
}


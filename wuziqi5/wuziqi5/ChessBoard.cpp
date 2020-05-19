#include "stdafx.h"
#include "ChessBoard.h"



ChessBoard::ChessBoard()
{
	memset(board, 0, sizeof(board));

	for (int i = 1; i <= maxn; i++)				// 初始化 初始值棋盘
		for (int j = 1; j <= maxn; j++)
		{
			pos_score[i][j] = maxn * 2 - abs(maxn - 2 * i) - abs(maxn - 2 * i);

		}

/*	type = { {0,0,0,0,0,0}, {0,1,1,1,1,1}, {0,1,1,1,1,0},{0,1,1,1,1,2},{0,1,1,0,1,1}, {0,1,1,1,0,1},
			 {0,1,1,1,0,0,}, {0,1,0,1,1,0}, {} };*/

}


ChessBoard::~ChessBoard()
{
}


HWND ChessBoard::drawBoard() {
	HWND h = initgraph(800, 540);
	setbkcolor(0xF3F8F1);
	cleardevice();

	IMAGE img;

	//加载图片
	loadimage(&img, _T("pic\\chessboard2.jpg"));
	putimage(0, 0, &img);
	return h;
}


int ChessBoard::changeColor(int now) {
	if (now == white)	now = black;
	else if (now == black)	now = white;

	return now;
}


int ChessBoard::getType(int x, int y) {
	return board[x][y];
}


bool ChessBoard::writeBoard(Chess c) {
	if (c.type == blank)	return false;
	if (board[c.x][c.y] != blank)	return false;

	board[c.x][c.y] = c.type;

	int x = (c.x - 1) * DEL + X0;
	int y = (c.y - 1) * DEL + X0;

	if (c.type == white) {
		setlinecolor(WHITE);
		setfillcolor(WHITE);
	}
	else{
		setlinecolor(BLACK);
		setfillcolor(BLACK);
	}

	fillcircle(x, y, CHESS_R);
	return true;
}


void ChessBoard::changeType(int x, int y, int type) {
	board[x][y] = type;
}


int ChessBoard::evaluate(int color) {

	int ans = 0, oppnent = changeColor(color);

	int range_searched[maxn + max_add][maxn + max_add];
	memset(range_searched, 0, sizeof(range_searched));
	
	for(int i = 1; i <= maxn; i++)
		for (int j = 1; j <= maxn; j++) {
			if (board[i][j] == color)
				ans += analyseNode(i, j);
			else if (board[i][j] = oppnent)
				ans -= analyseNode(i, j);
		}

	return ans;
}


int ChessBoard::analyseNode(int x, int y) {

	int dx[8] = { 1,0,-1, 0, 1,-1, 1, -1 }, yd[8] = { 0, 1, 0, -1, 1, -1, -1, 1 };
	int ans = 0, color = board[x][y], oppnent = changeColor(color);

	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 4; j++) {
			if (board[i][j] == oppnent)	break;
		}
	}

	return ans;
}
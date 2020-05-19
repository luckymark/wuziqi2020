#include "stdafx.h"
#include "ChessBoard.h"



ChessBoard::ChessBoard()
{
	memset(board, 0, sizeof(board));

	for (int i = 1; i <= maxn; i++)				// 初始化 初始值棋盘
		for (int j = 1; j <= maxn; j++)
		{
			pos_score[i][j] = maxn * 2 - abs(maxn - 2 * i) - abs(maxn - 2 * j);

		}

/*	type = { {0,0,0,0,0,0}, {0,1,1,1,1,1}, {0,1,1,1,1,0},{0,1,1,1,1,2},{0,1,1,0,1,1}, {0,1,1,1,0,1},
			 {0,1,1,1,0,0,}, {0,1,0,1,1,0}, {} };*/

	value[1] = 300000, value[2] = 30000, value[3] = 2500, value[4] = 3000, value[5] = 3300, value[6] = 500,
		value[7] = 800, value[8] = 600, value[9] = 200, value[10] = 2600;

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


bool ChessBoard::isIn(int x, int y) {
	return x >= 1 && x <= maxn && y >= 1 && y <= maxn;
}

int ChessBoard::evaluate(int color) {

	int ans = 0, oppnent = changeColor(color);

	int range_searched[maxn + max_add][maxn + max_add];
	memset(range_searched, 0, sizeof(range_searched));
	
	for(int i = 1; i <= maxn; i++)
		for (int j = 1; j <= maxn; j++) {
			if (board[i][j] == color)
				ans += analyseNode(i, j);
			else if (board[i][j] == oppnent)
				ans -= analyseNode(i, j);
		}

	return ans;
}


int ChessBoard::analyseNode(int x, int y) {

	int dx[8] = { 1,0,-1, 0, 1,-1, 1, -1 }, dy[8] = { 0, 1, 0, -1, 1, -1, -1, 1 };
	int ans = 0, color = board[x][y], oppnent = changeColor(color);

	for (int i = 1; i <= 8; i++) {
		int mine = 0, op = 0, bl = 0, n[5] = {0}, nx = x, ny = y;

		for (int j = 1; j <= 4; j++) {

			nx += dx[i];  ny += dy[i];

			if (nx < 1 || nx > maxn || ny < 1 || ny > maxn) {
				op += 4 - j + 1;
				break;
			}

			if (board[nx][ny] == color) {
				n[j] = 1;
				mine++;
			}
			else if (board[nx][ny] == oppnent) {
				n[j] = 0;
				op++;
			}
			else {
				n[j] = 2;
				bl++;
			}
		}

		
		if (mine == 4) {		// 连五
			ans += value[1];
			continue;
		}
		if (mine == 0) {
			continue;
		}


		bool back_blank = isIn(x - dx[i], y - dx[i]) && board[x - dx[i]][y - dx[i]] == blank;


		if (n[1] == 1 && n[2] == 1 && n[3] == 1) {	//连四
			if (n[4] == 2 && back_blank) {	// 活四
				ans += value[2];
				continue;
			}
			if (n[4] == 2 || back_blank) {	// 死四
				ans += value[3];
				continue;
			}
			continue;
		}

		if (mine == 3 && op == 0) {		// 其它死四
			if (n[3] == 2) {
				ans += value[4];
				continue;
			}
			else {
				ans += value[10];
				continue;
			}
		}

		if (n[1] == 1 && n[2] == 1) {

			if (n[3] == 2 && back_blank) {	// 活三
				ans += value[5];
				continue;
			}

			if (n[3] == 2 || back_blank) { // 死三
				ans += value[6];
				continue;
			}

			continue;
		}

		if (mine == 2 && bl == 2) {		// 其它死三，精简版
			ans += value[7];
			continue;
		}

		if (n[1] == 1) {
			if (bl == 3 && blank) {		// 活二
				ans += value[8];
				continue;
			}

			if (bl == 3) {		// 死二
				ans += value[9];
				continue;
			}
		}

		
	}

	return ans + pos_score[x][y];
}
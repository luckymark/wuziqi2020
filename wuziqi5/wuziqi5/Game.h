#pragma once
#include "chessboard.h"
#include "stdafx.h"

Chess calcPoint(int x, int y, int type);
void initGame(ChessBoard * board);
void gaming(ChessBoard * board);
bool judgeWin(Chess c, ChessBoard * board);
void showMessage(TCHAR * s);
Chess judgePos(int color, ChessBoard * board);
// void showMessage(int i);


HWND hwnd = 0;
const int maxn = ChessBoard::UPLIM;


void initGame(ChessBoard * board) {

	hwnd = board->drawBoard();

	setfillcolor(BLACK);
	fillrectangle(550, 20, 575, 45);

	setfillcolor(WHITE);
	fillrectangle(550, 60, 575, 85);

}


void gaming(ChessBoard * board) {
	int human_c = ChessBoard::black, robot_c = ChessBoard::white;

	int now = ChessBoard::black;

	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		switch (m.uMsg) {

		case WM_LBUTTONDOWN:
			Chess c;
			c = calcPoint(m.x, m.y, now);
			if (board->writeBoard(c)) {
				if (judgeWin(c, board))
					showMessage(_T("You Win!!!"));
				now = board->changeColor(now);

				c = judgePos(robot_c, board);
				if (board->writeBoard(c)) {
					if (judgeWin(c, board))
						showMessage(_T("Robot Win"));
				}
				now = board->changeColor(now);
			};
			break;
		default:
			break;
		}
	}
}


Chess calcPoint(int x, int y, int type) {		// untested
	Chess c; c.x = c.y = 0;

	int r = ChessBoard::DEL / 2;

	x = x - ChessBoard::X0;
	int n = x / ChessBoard:: DEL;
	if(n * ChessBoard::DEL - x != 0)
		if (abs(n * ChessBoard::DEL - x) <= r){
			c.x = n + 1;
		}
		else if (n * ChessBoard::DEL - x > 0){
			c.x = n;
		}
		else
		{
			c.x = n + 2;
		}
	
	y = y - ChessBoard::Y0;
	n = y / ChessBoard::DEL;
	if (n * ChessBoard::DEL - y != 0)
		if (abs(n * ChessBoard::DEL - y) <= r) {
			c.y = n + 1;
		}
		else if (n * ChessBoard::DEL - y > 0) {
			c.y = n;
		}
		else
		{
			c.y = n + 2;
		}

	if (!(c.x >= 1 && c.x <= ChessBoard::UPLIM && c.y >= 1 && c.y <= ChessBoard::UPLIM))
		c.type = ChessBoard::blank;
	else
	{
		c.type = type;
	}

	return c;
}


bool judgeWin(Chess c, ChessBoard * board) {

	int x[8] = { 1,-1,0, 0, 1,-1, 1, -1 }, y[8] = { 0, 0, 1, -1, 1, -1, -1, 1 };
	for (int i = 0; i < 8; i += 2) {
		for (int k = -4; k <= 0; k++) {

			int nx = c.x, ny = c.y, getOne = 0;
			nx += x[i] * k; ny += y[i] * k;
			if (!board->isIn(nx, ny)||(board->getType(nx, ny) != c.type))	continue;

			for (int j = 1; j <= 4; j++) {
				nx += x[i];
				ny += y[i];
				if (nx < 1 || nx > ChessBoard::UPLIM || ny < 1 || ny > ChessBoard::UPLIM)
					break;
				if (board->getType(nx, ny) != c.type)
					break;
				getOne++;
			}
			if (getOne == 4)	return true;
		}
	}

	return false;
}



void showMessage(TCHAR * s) {
	RECT r = { 550, 100, 790, 200 };
	setfillcolor(0xBACEC3);
	fillrectangle(550, 100, 790, 200);

	DrawText(GetDC(hwnd), s, -1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}


Chess judgePos(int color, ChessBoard * board) {
	

	Chess c = { 0,0,0 }; int nowVal = -23333333;

	for(int i = 1; i <= maxn; i++)			// findChess
		for (int j = 1; j <= maxn; j++)
		{
			if (board->getType(i, j) == ChessBoard::blank) {
				board->changeType(i, j, color);
				int val = board->evaluate(color);
				board->changeType(i, j, ChessBoard::blank);

				if (val > nowVal) {
					nowVal = val;
					c.x = i, c.y = j, c.type = color;
				}
			}
		}

	return c;
}
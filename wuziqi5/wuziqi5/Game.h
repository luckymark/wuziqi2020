#pragma once
#include "chessboard.h"
#include "stdafx.h"

Chess calcPoint(int x, int y, int type);
void initGame(ChessBoard * board);
void gaming(ChessBoard * board);
bool judgeWin(Chess c, ChessBoard * board);
void showMessage(TCHAR * s);
Chess judgePos(int color, ChessBoard * board);
void showColor(int human_color);
Chess minmax_search(int color, int depth, ChessBoard * board);
// void showMessage(int i);


HWND hwnd = 0;
const int maxn = ChessBoard::UPLIM;


void initGame(ChessBoard * board) {

	hwnd = board->drawBoard();

	showColor(ChessBoard::black);

}


void gaming(ChessBoard * board) {

	int human_c = ChessBoard::black, robot_c = ChessBoard::white;

	int now = ChessBoard::black, win = 0;

	showMessage(_T("RIGHT_BUTTON to Change"));

	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		switch (m.uMsg) {

		case WM_LBUTTONDOWN:
			if (win)	break;
			Chess c;
			c = calcPoint(m.x, m.y, now);
			if (board->writeBoard(c)) {
				if (judgeWin(c, board)) {
					showMessage(_T("You Win!!!"));
					win = now;
					continue;
				}
				now = board->changeColor(now);

//				c = judgePos(robot_c, board);
				c = minmax_search(now, 4, board);

				if (board->writeBoard(c)) {
					if (judgeWin(c, board)) {
						showMessage(_T("Robot Win"));
						win = now;
						continue;
					}
				}
				now = board->changeColor(now);
			};
			break;

		case WM_RBUTTONDOWN:
			if (win)	break;
			human_c = board->changeColor(human_c);
			robot_c = board->changeColor(robot_c);
			showColor(human_c);

//			c = judgePos(robot_c, board);
			c = minmax_search(robot_c, 3, board);

			if (board->writeBoard(c)) {
				if (judgeWin(c, board)) {
					showMessage(_T("Robot Win"));
					win = now;
					continue;
				}
			}
			now = board->changeColor(now);
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


void showColor(int human_color) {

	setlinecolor(0xF3F8F1);		// ±ß¿òÑÕÉ«

	setfillcolor(BLACK);
	fillrectangle(550, 20, 575, 45);

	setfillcolor(WHITE);
	fillrectangle(550, 60, 575, 85);

	RECT r1 = { 580, 20, 630, 45 }, r2 = { 580, 60, 630, 85 };
	setfillcolor(0xF3F8F1);
	
	fillrectangle(580, 20, 630, 45);
	fillrectangle(580, 60, 630, 85);

	if (human_color == ChessBoard::black) {
		RECT t = r1;
		r1 = r2;
		r2 = t;
	}
	
	DrawText(GetDC(hwnd), _T("Human"), -1, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(GetDC(hwnd), _T("Robot"), -1, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}


Chess judgePos(int color, ChessBoard * board) {		// judge best chess
	

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


Chess minmax_search(int color, int depth, ChessBoard * board) {
	Chess ans = { 0,0,0 };
	int now_color = color, max_val = -23333333;
	for(int i = 1; i <= maxn; i++)
		for (int j = 1; j <= maxn; j++) {

			if (board->getType(i, j) == ChessBoard::blank) {
				Chess c[10];
				c[1] = { i ,j, color };
				board->changeType(i, j, color);


				int t = 1;
				if (depth >= 2) {
					for (t = 2; t <= depth; t++) {	// ×î¶à9²ã
						now_color = board->changeColor(now_color);
						c[t] = judgePos(now_color, board);
						board->changeType(c[t].x, c[t].y, now_color);
						if (judgeWin(c[t], board)) {
							t++;
							break;
						}
					}
				}

				int val = board->evaluate(color);
				if (val > max_val) {
					ans = c[1];
					max_val = val;
				}

				for (t-- ; t >= 2; t--) {
					board->changeType(c[t].x, c[t].y, ChessBoard::blank);
					now_color = board->changeColor(now_color);
				}


				board->changeType(i, j, ChessBoard::blank);
			}
		}
	return ans;
}
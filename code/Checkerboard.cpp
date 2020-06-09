#include "Checkerboard.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <easyx.h>

#define LENGTH 15
#define HALF 4

Checkerboard::Checkerboard() {
	init();
}


const int FRONT[4][2] = { {1, 0},    //DOWN
						 {0, 1},    //RIGHT
						 {1, 1},    //DR
						 {1, -1} };  //DL

void Checkerboard::init()
{
	memset(board, 0, sizeof(board));
}

bool Checkerboard::set_chess(int x, int y, int c) {
	if (!inside(x, y)) {
		return false;
	}
	if (board[x][y]) {
		return false;
	}
	else {
		board[x][y] = c;
		return true;
	}
}

bool Checkerboard::judge(int x, int y, int c) {
	for (int i = 0; i < 4; ++i) {
		int* line = get_line(x, y, i);
		int cnt = count(line);
		delete line;
		line = nullptr;
		if (cnt >= 5) {
			return true;
		}
	}
	return false;
}

//使用后请delete掉
int* Checkerboard::get_line(int x, int y, int front) {
	int* line = new int[9];
	if (line == nullptr) {
		exit(-1);
	}
	memset(line, -1, sizeof(int) * 9);
	int dx = FRONT[front][0], dy = FRONT[front][1];
	for (int i = -HALF; i <= HALF; ++i) {
		if (inside(x + i * dx, y + i * dy))
			line[i + HALF] = board[x + i * dx][y + i * dy];
	}
	return line;
}

bool Checkerboard::inside(int x, int y) {
	return x >= 0 && x < LENGTH && y >= 0 && y < LENGTH;
}

void Checkerboard::print_init()
{
	initgraph(680,680);
	settextcolor(RED);
	setbkcolor(WHITE);
	setlinecolor(BLACK);
	cleardevice();
}

void Checkerboard::print_board()
{
	for (int i = 1; i <= 15; i++) {
		line(40 * i, 40, 40 * i, 600);
		line(40, 40 * i, 600, 40 * i);
	}
}

void Checkerboard::print_chess()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j]) {
				if (board[i][j] == 1) {
					setfillcolor(BLACK);
					fillcircle(40 * (j+1), 40 * (i+1), 15);
				}
				else {
					setfillcolor(WHITE);
					fillcircle(40 * (j+1), 40 * (i+1), 15);
				}
			}
		}
	}
}

void Checkerboard::print_win()
{
	settextcolor(BLACK);
	outtextxy(320, 200, "游戏结束！");
	outtextxy(310, 220, "按任意键退出");
}

int Checkerboard::count(const int* x) {
	int cnt = 0, max = 0;
	int color = x[HALF];
	for (int i = 0; i < 2 * HALF + 1; ++i) {
		if (x[i] == color) {
			cnt++;
			if (cnt > max) max = cnt;
		}
		else {
			cnt = 0;
		}
	}
	return max;
}
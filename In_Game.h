#ifndef IN_GAME_H
#define IN_GAME_H

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
const int x_o = 20, y_o = 20;
const int WIDTH = 30;           //¸ñ×Ó¼ä¾à
const int SIZES = 15;
int chess_board[SIZES + 5][SIZES + 5];
void Mouse_event() {
	MOUSEMSG M;
	while (true) {
		M = GetMouseMsg();
		int a, b, x, y;
		for (int i = 0; i < SIZES; i++) {
			for (int j = 0; j < SIZES; j++) {
				if (abs(M.x - (x_o + i * WIDTH)) < 15 && abs(M.y - (y_o + j * WIDTH)) < 15) {
					a = i;
					b = j;
					x = i * WIDTH;
					y = j * WIDTH;
				}
			}
		}
		if (M.uMsg == WM_LBUTTONDOWN) {
			if (!chess_board[a][b]) {
				setfillcolor(BLACK);
				solidcircle(x, y, 10);
				chess_board[a][b] = 1;
				break;
			}
		}

	}
	//for(int i=1)
}

#endif
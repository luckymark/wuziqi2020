//#pragma comment(lib,"User32.lib")
#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
//#pragma comment(lib,"ws2_32.lib")
extern int chess_board[25][25];
extern int a, b, x, y;
void Mouse_event() {
	const int x_o = 20, y_o = 20;
	const int WIDTH = 30;           //¸ñ×Ó¼ä¾à
	const int SIZES = 15;
	MOUSEMSG M;
	while (true) {
		M = GetMouseMsg();
		for (int i = 0; i < SIZES; i++) {
			for (int j = 0; j < SIZES; j++) {
				if (abs(M.x - (x_o + i * WIDTH))<15 && abs(M.y - (y_o + j * WIDTH))<15){
					a = i;
					b = j;
					x = x_o + (i)*WIDTH;
					y = y_o + (j)*WIDTH;
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
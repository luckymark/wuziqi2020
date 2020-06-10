#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include "Set_graph.h"
#include "Mouse_Event.h"
#include "Check_win.h"

//#include "score_count.h"
#include "min_max.h"
//IMAGE	Windows;
//#pragma comment(lib,"User32.lib")
//#pragma comment(lib,"ws2_32.lib")
int a, b, x, y;
int chess_board[25][25];

enum players {
	player = 1,
	AI
};
int main() {
	HWND hwnd;
	hwnd = GetHWnd(); //设置窗口句柄
	show_image();
	int flag = 1;
	while (1) {
		if (flag % 2) {
			Mouse_event();
			if (judge(a, b, player, chess_board)) {
				MessageBox(hwnd, "You are winner!", "游戏结束", MB_OK);
				break;
			}
		}else {
			int choose_x = 0;
			int choose_y = 0;
			AImax_search(choose_x, choose_y, 2);
			chess_board[choose_x][choose_y] = AI;
			setfillcolor(WHITE);
			solidcircle(20 + (choose_x * 30), 20 + (choose_y * 30), 10);
			if (judge(choose_x, choose_y, AI, chess_board)) {
				MessageBox(hwnd, "You are defeated!", "游戏结束", MB_OK);
				break;
			}
		}
		flag++;
	}
	closegraph();
	return 0;
}

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include "draw.h"
#include "gamerun.h"
#include "GameManagement.h"
int main()
{
	initgraph(800, 600);
	Draw_board();
	gamerun();
	game_again();
	_getch();              // 按任意键继续
	closegraph();          // 关闭绘图窗口
	return 0;
}


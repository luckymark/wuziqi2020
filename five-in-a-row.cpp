#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include"Draw.h"
#include"Gamerun.h"
#include"AI.h"
//#include<EasyX.h>

///*定数组大小*/
//#define N 15
//int status[N][N] = { 0 };





int main()
{
	initgraph(800, 600);   //初始化图形系统（游戏外形大小）
	GameRun();
	//_getch();
	closegraph();
	return 0;
}



#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include"Draw.h"
#include"AI.h"
//#include"rule.h"
//#include"test.h"


/////*定数组大小*/
#define N 15
int status[N][N] = { 0 };
int ResultCheck(int x, int y, int i);


void GameRun()
{
	setbkcolor(GREEN);
	cleardevice();
	IMAGE img = NULL, IMG_WHITE = NULL, IMG_BLACK = NULL;    //定义保存图像的指针
	MOUSEMSG m;
	int x = 0, y = 0, xx = 0, yy = 0;
	//int xb = 0, yb = 0, xw = 0, yw = 0;
	int AIplay[2];
	//int olds[15][15] = { 0 };
	//int news[15][15] = { 0 };
	int i = 0, a = 0;      //计数器
	DrawBoard();      //调用棋盘

	while (1)
	{
		if (i % 2 == 0)
		{
			ShowMessage(i);
			if (MouseHit())
			{
				m = GetMouseMsg();      //获取鼠标坐标
				FlushMouseMsgBuffer();
				if (m.uMsg == WM_LBUTTONDOWN)
				{
					i++;
					x = m.x / 40;       //鼠标坐标转化棋盘坐标
					y = m.y / 40;       //鼠标坐标转化棋盘坐标
					if ((x >= 0 && x < 15) && (y >= 0 && y < 15) && status[x][y] == 0)     //限制落子在棋盘范围内,且不能落在已存在棋子的点上
					{
						//getimage(&IMG_BLACK, x * 40, y * 40, 80, 80);   //把落子前的图案放到指针里，悔棋时，将调用此图，把棋子覆盖掉，回到落子前的状态
						//xb = x; yb = y;
						DrawCircle(x, y, BLACK);       //调用棋子	
						//HeQi(i);                      //调用和棋函数体
						status[x][y] = 1;                //定义黑棋玩家在数组内为1（在检查结果时使用）
						if (i == 225)                     //判断棋盘是否画满
							break;
						if (ResultCheck(x, y, i))      //根据*检查结果*函数体的返回值，输出结果
						{
							//loadimage(&img, _T("..\\HEI.jpg"));   //调用*黑棋获胜！*图片
							//putimage(120, 200, &img);
							printf("You are win.");
							break;
						}
					}
				}
			}
		}
		else{
					ShowMessage(i);
					i++;
					Sleep(1000);
					AI(status,/* olds,*/ AIplay);
					xx = AIplay[0];
					yy = AIplay[1];
					//getimage(&IMG_WHITE, xx * 40, yy * 40, 80, 80);      //把落子前的图案放到指针里，悔棋时，将调用此图，把棋子覆盖掉，回到落子前的状态
					//xw = xx; yw = yy;
					DrawCircle(xx, yy, WHITE);        //调用棋子
					//HeQi(i);                       //调用和棋函数体
					status[xx][yy] = 2;                 //定义白棋玩家在数组内为2（在检查结果时使用）
					if (i == 225)
						break;
					if (ResultCheck(xx, yy, i))        //根据*检查结果*函数体的返回值，输出结果
					{
						//loadimage(&img, _T("..\\BAI.jpg"));  //调用*白棋获胜！*图片
						//putimage(120, 200, &img);
						printf("You are lost");
						break;
					}

				}
	}
}



/*检查结果*/
int ResultCheck(int x, int y, int i)
{
	int j, k, color;
	int n1, n2;  //计数器，用于累计棋子个数


	if (i % 2 == 0)      //根据计数器i的奇偶性，切换黑棋和白棋的检查
		color = 2;
	else
		color = 1;

	while (1)
	{
		n1 = 0;
		n2 = 0;
		for (j = x, k = y; j >= 0; j--)                      //向左检查
		{
			if (status[j][k] == color)                     //判断是否为黑子
				n1++;
			else
				break;
		}
		for (j = x, k = y; j < 15; j++)                            //向右检查
		{
			if (status[j][k] == color)
				n2++;
			else
				break;
		}
		if (n1 + n2 - 1 >= 5)
		{
			return(1);
		}
		n1 = 0;
		n2 = 0;
		for (j = x, k = y; k >= 0; k--)                                //向上检查
		{
			if (status[j][k] == color)
				n1++;
			else
				break;
		}
		for (j = x, k = y; k < 15; k++)                               //向下检查
		{
			if (status[j][k] == color)
				n2++;
			else
				break;
		}
		if (n1 + n2 - 1 >= 5)
		{
			return(1);
		}
		n1 = 0;
		n2 = 0;
		for (j = x, k = y; (j >= 0) && (k >= 0); j--, k--)                    //向左上检查
		{
			if (status[j][k] == color)
				n1++;
			else
				break;
		}
		for (j = x, k = y; (j < 15) && (k < 15); j++, k++)                      //向右下检查
		{
			if (status[j][k] == color)
				n2++;
			else
				break;
		}
		if (n1 + n2 - 1 >= 5)
		{
			return(1);
		}
		n1 = 0;
		n2 = 0;
		for (j = x, k = y; (j < 15) && (k >= 0); j++, k--)                    //向右上检查
		{
			if (status[j][k] == color)
				n1++;
			else
				break;
		}
		for (j = x, k = y; (j >= 0) && (k < 15); j--, k++)                       //向左下检查
		{
			if (status[j][k] == color)
				n2++;
			else
				break;
		}
		if (n1 + n2 - 1 >= 5)
		{
			return(1);
		}
		return(0);
	}
}

#include <stdio.h>
#include <graphics.h>
#include "gamerun.h"
void game_again();
void HeQi(int i);

void game_again()
{
	MOUSEMSG m;
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			FlushMouseMsgBuffer();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (m.x <= 770 && m.x >= 620 && m.y <= 345 && m.y >= 300)    //“重新开始”伪按钮(游戏结束时才可使用)
				{
					gamerun();
				}
				if (m.x <= 770 && m.x >= 620 && m.y <= 490 && m.y >= 450)    //“退出游戏”伪按钮(游戏结束时才可使用)
				{
					exit(0);
				}
			}
		}
	}
}

void HeQi(int i)
{
	IMAGE img;
	if (i == 225)
	{
		loadimage(&img, _T("C:\\Users\\皮卡c\\Desktop\\人机对战\\五子棋\\HEQI.jpg"));
		putimage(200, 280, &img);
		
	}
}

int ResultCheck(int x, int y, int i,int status[15][15])
{
	int j, k, h;
	int n1, n2;                           //计数器，用于累计棋子个数

	if (i % 2 == 0)
	{
			h = 2;
	}//根据计数器i的奇偶性，切换黑棋和白棋的检查
		
	else
	{
			h = 1;
	}
		

	while (1)
	{
		n1 = 0;
		n2 = 0;
		for (j = x, k = y; j >= 0; j--)                      //向左检查
		{
			if (status[j][k] == h)                     //判断是否为黑子
				n1++;
			else
				break;
		}
		for (j = x, k = y; j < 15; j++)                            //向右检查
		{
			if (status[j][k] == h)
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
			if (status[j][k] == h)
				n1++;
			else
				break;
		}
		for (j = x, k = y; k < 15; k++)                               //向下检查
		{
			if (status[j][k] == h)
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
			if (status[j][k] == h)
				n1++;
			else
				break;
		}
		for (j = x, k = y; (j < 15) && (k < 15); j++, k++)                      //向右下检查
		{
			if (status[j][k] == h)
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
			if (status[j][k] == h)
				n1++;
			else
				break;
		}
		for (j = x, k = y; (j >= 0) && (k < 15); j--, k++)                       //向左下检查
		{
			if (status[j][k] == h)
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
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
//#include<EasyX.h>


/*画棋子*/
void DrawCircle(int x, int y, int color)
{
	setcolor(color);
	setlinestyle(PS_SOLID, 2);
	x = x * 40 + 20;
	y = y * 40 + 20;
	setfillcolor(color);
	fillcircle(x, y, 12);
}


/*显示落子玩家*/
int ShowMessage(int i)
{
	if (i < 225)
	{
		if (i % 2 == 0)
		{
			setcolor(BLACK);
			setlinestyle(PS_SOLID, 2);
			setfillcolor(BLACK);
			fillcircle(700, 150, 20);
		}
		else
		{
			setcolor(WHITE);
			setlinestyle(PS_SOLID, 2);
			setfillcolor(WHITE);
			fillcircle(700, 150, 20);
		}
	}
	else
	{
		return(1);
	}
}




void DrawBoard()
{
	int i;
	//loadimage(NULL, _T("..\\ShuiMo.jpg"));   //用相对路径调用背景图片
	setcolor(WHITE);       //线条颜色
	setlinestyle(PS_SOLID, 2);     //线条样式
	for (i = 0; i != 15; ++i)
	{
		line(16, 16, 584, 16);       //画外围边框
		line(16, 584, 584, 584);
		line(16, 16, 16, 584);
		line(584, 16, 584, 584);

		line(20, 40 * i + 20, 580, 40 * i + 20);  //画小方格的横线
		line(40 * i + 20, 20, 40 * i + 20, 580);  //画小方格的竖线
	}

	//setfillstyle(WHITE);           //画棋盘上的五个点
	setfillcolor(WHITE);
	fillcircle(300, 300, 4);
	fillcircle(140, 140, 4);
	fillcircle(140, 460, 4);
	fillcircle(460, 140, 4);
	fillcircle(460, 460, 4);

	setcolor(BLACK);          //提示先手玩家为黑棋
	setlinestyle(PS_SOLID, 2);
	setfillcolor(BLACK);
	fillcircle(700, 150, 20);

}
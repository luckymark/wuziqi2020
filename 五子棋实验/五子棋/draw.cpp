#include <graphics.h>
#include <conio.h>
void Draw_board();
void Draw_Circle(int x,int y,int circle_color);


void Draw_board()
{
	setbkcolor(BROWN);
	cleardevice();//设置背景为白色

	setcolor(BLACK);       //线条颜色(黑色)
	setlinestyle(PS_SOLID, 2);     //线条样式(实线 宽度为2)

	line(16, 16, 584, 16);
	line(16, 584, 584, 584);
	line(16, 16, 16, 584);
	line(584, 16, 584, 584);		//画外围边框

	for (int i = 0; i < 15; ++i)    //标准棋盘（15 X 15）
	{

		line(20, 40 * i + 20, 580, 40 * i + 20);  //画小方格的横线
		
		line(40 * i + 20, 20, 40 * i + 20, 580);  //画小方格的竖线

	}

	setfillstyle(BLACK);           
	setfillcolor(BLACK);
	fillcircle(300, 300, 4);
	fillcircle(140, 140, 4);
	fillcircle(140, 460, 4);
	fillcircle(460, 140, 4);
	fillcircle(460, 460, 4);					//画棋盘上的五个点(黑色)

	//setcolor(BLACK);          //提示先手玩家为黑棋
	//setlinestyle(PS_SOLID, 2);
	//setfillcolor(BLACK);
	//fillcircle(700, 150, 20);
	RECT r = { 620, 345, 770, 300 };
	drawtext(_T("重新开始"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT a = { 620, 450, 770, 490};
	drawtext(_T("退出游戏"), &a, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void Draw_Circle(int x,int y,int circle_color)
{
	x = x * 40 + 20;
	y = y * 40 + 20;
	setfillcolor(circle_color);
	fillcircle(x, y, 12);
}
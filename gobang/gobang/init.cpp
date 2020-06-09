#include<graphics.h>
#include<conio.h>

void initboard()//初始化棋盘图形界面
{
	initgraph(600, 600);
	setorigin(55, 55);
	setbkcolor(RGB(46, 139, 87));
	//46, 139, 87
	//238, 180, 34
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	setfillcolor(BLACK);
	const int width = 35;
	for (int i = 0; i <= width * 14; i += width)
		line(i, 0, i, width * 14);
	for (int i = 0; i <= width * 14; i += width)
		line(0, i, width * 14, i);
	for (int i = width * 3; i <= width * 11; i += width * 4)
		for (int j = width * 3; j <= width * 11; j += width * 4)
			fillcircle(i, j, 4);
}
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include"wuziqi.h"

extern int whostart;
extern int chess[16][16];
extern CURRENT now;
extern int steps;
extern int computerx, computery;

void putmap()						// 打开地图。
{
	initgraph(1200, 800, EW_SHOWCONSOLE);
	setbkcolor(GREEN);
	cleardevice();
	setcolor(WHITE);
	for (int i = 50; i <= 750; i += 50)
	{
		line(50, i, 750, i);
		line(i, 50, i, 750);
	}
	POINT pts1[] = { {800, 50}, {800, 100}, {1100, 100},{1100, 50} };
	fillpolygon(pts1, 4);
	RECT r1 = { 800, 50, 1100, 100 };

	drawtext(_T("Restart"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	POINT pts2[] = { {800, 200}, {800, 250}, {1100, 250},{1100, 200} };
	fillpolygon(pts2, 4);
	RECT r2 = { 800, 200, 1100, 250 };
	drawtext(_T("Undo"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r5 = { 800, 350, 1100, 400 };
	drawtext(_T("Before play, choose from the following options"), &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	POINT pts3[] = { {800, 450}, {800, 500}, {1100, 500},{1100, 450} };
	fillpolygon(pts3, 4);
	RECT r3 = { 800, 450, 1100, 500 };
	drawtext(_T("Player First"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	POINT pts4[] = { {800, 600}, {800, 650}, {1100, 650},{1100, 600} };
	fillpolygon(pts4, 4);
	RECT r4 = { 800, 600, 1100, 650 };
	drawtext(_T("Computer first"), &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (800 <= m.x && m.x <= 1100 && m.y >= 450 && m.y <= 500)
				whostart = 1;
			else if (800 <= m.x && m.x <= 1100 && m.y >= 600 && m.y <= 650)
				whostart = -1;
			break;
		default: break;
		}
		if (whostart != 0)
			break;
	}
	if (whostart == 1)
	{
		RECT r6 = { 800, 450, 1100, 500 };
		drawtext(_T("Player First(your choice)"), &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else if (whostart == -1)
	{
		RECT r7 = { 800, 600, 1100, 650 };
		drawtext(_T("Computer First(your choice)"), &r7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

void playchess(void)					// 玩家游戏
{
	int flag = 0;
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (25 <= m.x && m.x < 775 && m.y >= 25 && m.y < 775 && chess[(int)((m.y + 25) / 50)][(int)((m.x + 25) / 50)] == 0)
			{
				chess[(int)((m.y + 25) / 50)][(int)((m.x + 25) / 50)] = 1;
				setcolor(WHITE);
				setfillcolor(WHITE);
				fillcircle(50* (int)((m.x + 25) / 50),50* (int)((m.y + 25) / 50),10);
				now.x = (int)((m.y + 25) / 50);
				now.y = (int)((m.x + 25) / 50);
				flag = 1;
			}
			break;
		default: break;
		}
		if (flag == 1)
			return;
	}
}

bool win(int x,int y, int map[16][16])					// 判断是否游戏结束
{
	int a = map[x][y];
	if (a == 0)
		return 0;
	int i,j,sum = 0;					
	for (i = max(1, x - 4),sum=0; i <= min(15, x + 4); i++)					// judge if the game is over on the line.
	{
		if (sum > 4)
			break;
		else if (map[i][y] != a)
			sum = 0;
		else
			sum++;
	}
	if (sum == 5)
		return 1;
	for (j = max(1, y - 4), sum = 0; j <= min(15, y + 4); j++)				// judge if the game is over on the colume.
	{
		if (sum > 4)
			break;
		else if (map[x][j] != a)
			sum = 0;
		else
			sum++;
	}
	if (sum == 5)
		return 1;
	for (sum = 0, i = x - 4, j = y - 4; i <= x + 4 && j <= y + 4; i++, j++)	// judge if the game if over on the oblique.
	{
		if (i < 1 || i>15 || j < 1 || j>15)
			continue;
		if (sum > 4)
			break;
		else if (map[i][j] != a)
			sum = 0;
		else
			sum++;
	}
	if (sum == 5)
		return 1;
	for (sum = 0, i = x - 4, j = y + 4; i <= x + 4 && j >= y - 4; i++, j--)	// judge if the game is over on the oblique.
	{
		if (i < 1 || i>15 || j < 1 || j>15)
			continue;
		if (sum > 4)
			break;
		else if (map[i][j] != a)
			sum = 0;
		else
			sum++;
	}
	if (sum == 5)
		return 1;
	return 0;
}

void computerchess(void)		// 电脑下棋
{
	if (steps == 0)
	{
		computerx = 8;
		computery = 8;
	}
	else
	{
		maxmin(chess,DEPTH,NINF,PINF);
	}
	setcolor(BLACK);
	setfillcolor(BLACK);
	//printf("%d %d", computerx, computery);
	fillcircle(50 * computery, 50 * computerx, 10);
	chess[computerx][computery] = 2;
	now.x = computerx;
	now.y = computery;
}
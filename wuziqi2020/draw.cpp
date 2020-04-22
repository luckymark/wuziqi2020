////////////////////////////////////////////////////////
// 程序名称：博弈五子棋
// 编译环境：Visual C++ 2019		EasyX_20190529(beta)
// 作　　者：陈可佳 <emil09_chen@126.com>
// 最后修改：2019-9-30
//
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "draw.hpp"
#include "func.hpp"



// 全局变量
box BOX[15][15];      // 棋盘
int win = -1;         // 谁赢了（0：白棋，1：黑棋，2：平局）
int whoplay = 0;      // 轮到谁下棋了
int playercolor = 0;  // 玩家颜色
int dx[4]{ 1,0,1,1 }; // - | \ / 四个方向
int dy[4]{ 0,1,1,-1 };
seat findbestseat2(int); // 我的函数

// main 函数
int main()
{
	initgraph(580, 580, NOMINIMIZE); // 初始化绘图环境
	setbkcolor(RGB(255, 205, 150));
	cleardevice();
	setbkmode(TRANSPARENT); // 设置透明文字输出背景
	while (1)
	{
		init(); // 初始化
		game(); // 游戏开始
		cleardevice();
	}
}

// 类函数定义

// 绘制函数
void box::draw()
{
	COLORREF thefillcolor = getfillcolor(); // 备份填充颜色
	setlinestyle(PS_SOLID, 2);              // 线样式设置
	setfillcolor(color);                    // 填充颜色设置
	solidrectangle(x, y, x + 30, y + 30);   // 绘制无边框的正方形
	if (isnew)
	{
		// 如果是新下的
		// 绘制边框线
		setlinecolor(LIGHTGRAY);
		line(x + 1, y + 2, x + 8, y + 2);
		line(x + 2, y + 1, x + 2, y + 8);
		line(x + 29, y + 2, x + 22, y + 2);
		line(x + 29, y + 1, x + 29, y + 8);
		line(x + 2, y + 29, x + 8, y + 29);
		line(x + 2, y + 22, x + 2, y + 29);
		line(x + 29, y + 29, x + 22, y + 29);
		line(x + 29, y + 22, x + 29, y + 29);
	}
	setlinecolor(BLACK);
	switch (modle)
	{
		// 以下是不同位置棋盘的样式
	case 0:
		line(x + 15, y, x + 15, y + 30);
		line(x - 1, y + 15, x + 30, y + 15);
		break;
		//  *
		// ***
		//  *
	case 1:
		line(x + 14, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// *
		// ***
		// *
	case 2:
		line(x - 1, y + 15, x + 15, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		//   *
		// ***
		//   *
	case 3:
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		// ***
		//  *
		//  *
	case 4:
		line(x + 15, y, x + 15, y + 15);
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		//  *
		//  *
		// ***
	case 5:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 15);
		line(x + 15, y + 15, x + 30, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		// *
		// *
		// ***
	case 6:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y, x + 15, y + 15);
		line(x - 1, y + 15, x + 15, y + 15);
		setlinestyle(PS_SOLID, 2);
		break;
		//   *
		//   *
		// ***
	case 7:
		setlinestyle(PS_SOLID, 3);
		line(x - 1, y + 15, x + 15, y + 15);
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// ***
		//   *
		//   *
	case 8:
		setlinestyle(PS_SOLID, 3);
		line(x + 15, y + 15, x + 30, y + 15);
		line(x + 15, y + 15, x + 15, y + 30);
		setlinestyle(PS_SOLID, 2);
		break;
		// ***
		// *
		// *
	case 9:
		line(x + 15, y, x + 15, y + 30);
		line(x - 1, y + 15, x + 30, y + 15);
		setfillcolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 4);
		break;
		//  *
		// *O*
		//  *
	}
	switch (color_val)
	{
	case 0: // 白棋
		setfillcolor(WHITE);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 13);
		break;
	case 1: // 黑棋
		setfillcolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		fillcircle(x + 15, y + 15, 13);
		break;
	}
	setfillcolor(thefillcolor); // 还原填充色
}



// 其他函数定义

// 绘制棋盘
void draw()
{
	int modle = 0;  // 棋盘样式
	int number = 0; // 坐标输出的位置
	// 坐标（数值）
	TCHAR strnum[15][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),
							_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") ,
							_T("14"),_T("15") };
	// 坐标（字母）
	TCHAR strabc[15][3] = { _T("A"),_T("B") ,_T("C") ,_T("D"),_T("E") ,_T("F") ,_T("G"),
							_T("H"),_T("I"),_T("J"), _T("K"),_T("L") ,_T("M") ,
							_T("N"),_T("O") };
	for (int i = 0, k = 0; i < 450; i += 30)
	{
		for (int j = 0, g = 0; j < 450; j += 30)
		{
			BOX[k][g].color = RGB(255, 205, 150);// 棋盘底色
			// x y 坐标
			BOX[k][g].x = 65 + j;
			BOX[k][g].y = 50 + i;
			BOX[k][g].score = 0;// 初始化分数
			// 棋盘样式的判断
			if (k == 0 && g == 0)
			{
				modle = 8;
			}
			else if (k == 0 && g == 14)
			{
				modle = 7;
			}
			else if (k == 14 && g == 14)
			{
				modle = 6;
			}
			else if (k == 14 && g == 0)
			{
				modle = 5;
			}
			else if (k == 0)
			{
				modle = 3;
			}
			else if (k == 14)
			{
				modle = 4;
			}
			else if (g == 0)
			{
				modle = 1;
			}
			else if (g == 14)
			{
				modle = 2;
			}
			else if ((k == 3 && g == 3) || (k == 3 && g == 11) || (k == 11 && g == 3) || 
						(k == 11 && g == 11) || (k == 3 && g == 7) || (k == 7 && g == 3) || 
						(k == 11 && g == 7) || (k == 7 && g == 11) || (k == 7 && g == 7)) {
				modle = 9;
			}
			else
			{
				modle = 0;
			}
			BOX[k][g].modle = modle;
			BOX[k][g].draw(); // 绘制
			if (BOX[k][g].isnew == true)
			{
				BOX[k][g].isnew = false; // 把上一个下棋位置的黑框清除
			}
			g++;
		}
		k++;
	}
	// 画坐标
	LOGFONT nowstyle;
	gettextstyle(&nowstyle);
	settextstyle(0, 0, NULL);
	for (int i = 0; i < 15; i++)
	{
		outtextxy(75 + number, 35, strnum[i]);
		outtextxy(53, 55 + number, strabc[i]);
		number += 30;
	}
	settextstyle(&nowstyle);
}

// 对局初始化
void init()
{
	win = -1;// 谁赢了
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			BOX[i][j].score = 0;// 分数
			BOX[i][j].color_val = -1;// 值
			neighbor[i][j] = 0;// init neighbor
		}
	}
}



// 核心函数

// 寻找最佳位置
seat findbestseat1(int color)
{
	// 评分表
	int Score[3][5] = {
		{ 0, 20, 360, 5800, 92840 }, // 防守0子
		{ 0, 0, 20, 360, 92840 },    // 防守1子
		{ 0, 0, 0, 0, 92840 }        // 防守2子
	};
	seat bestseat;              // 最佳位置
	int MAXnumber[225] = { 0 }; // 最佳分数（可能有多个）
	int MAXx[225] = { 0 };      // 最佳 x 坐标（可能有多个）
	int MAXy[225] = { 0 };      // 最佳 y 坐标（可能有多个）
	int number = 0;             // 下一个最佳分数储存位置
	int truenumber;             // 输出的最佳分数位置
	int nowi = 0;               // 现在遍历到的y坐标
	int nowj = 0;               // 现在遍历到的x坐标
	int length[4];              // 四个方向的长度
	int enemy[4];               // 四个方向的敌子
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (BOX[i][j].color_val == -1)
			{
				// 遍历每一个可能的位置

				// 自己
				BOX[i][j].color_val = color; // 尝试下在这里
				for (int k = 0; k < 4; k++)
				{
					length[k] = 0;
					enemy[k] = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].color_val == color)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					if (BOX[nowi][nowj].color_val == 1 - color || nowi < 0 || nowj < 0 || nowi > 14 || nowj > 14)
					{
						enemy[k]++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].color_val == color)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
					if (BOX[nowi][nowj].color_val == 1 - color || nowi < 0 || nowj < 0 || nowi > 14 || nowj > 14)
					{
						enemy[k]++;
					}
					length[k] -= 2; // 判断长度
					if (length[k] > 4)
					{
						length[k] = 4;
					}
					BOX[i][j].score += Score[enemy[k]][length[k]] * 4 + !(!length[k]) * 20;//加分系统
					length[k] = 0;
					enemy[k] = 0;
				}
				// 敌人（原理同上）
				BOX[i][j].color_val = 1 - color;
				for (int k = 0; k < 4; k++)
				{
					length[k] = 0;
					enemy[k] = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].color_val == 1 - color)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					if (BOX[nowi][nowj].color_val == color || nowi < 0 || nowj < 0 || nowi > 14 || nowj > 14)
					{
						enemy[k]++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].color_val == 1 - color)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
					if (BOX[nowi][nowj].color_val == color || nowi < 0 || nowj < 0 || nowi > 14 || nowj > 14)
					{
						enemy[k]++;
					}
					length[k] -= 2;
					if (length[k] > 4)
					{
						length[k] = 4;
					}
					BOX[i][j].score += Score[enemy[k]][length[k]];
					length[k] = 0;
					enemy[k] = 0;
				}
				BOX[i][j].color_val = -1;
			}
			if (BOX[i][j].score == MAXnumber[0])
			{
				// 如果和最高分数相同
				MAXnumber[number] = BOX[i][j].score;
				MAXy[number] = i;
				MAXx[number] = j;
				number++;
				// 新增一个分数及坐标
			}
			if (BOX[i][j].score > MAXnumber[0])
			{
				// 如果比最高分数高
				for (int k = 0; k < number; k++)
				{
					MAXnumber[k] = 0;
					MAXy[k] = 0;
					MAXx[k] = 0;
				}
				number = 0;
				MAXnumber[number] = BOX[i][j].score;
				MAXy[number] = i;
				MAXx[number] = j;
				number++;
				// 清空数组再加入
			}
		}
	}
	// 生成随机位置
	srand(time(NULL));
	truenumber = rand() % number;
	bestseat.i = MAXy[truenumber];
	bestseat.j = MAXx[truenumber];
	bestseat.score = MAXnumber[truenumber];
	// 返回位置
	return bestseat;
}

// 判断输赢
void isWIN()
{
	bool isinit = true; // 是否刚刚开局
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (BOX[i][j].color_val != -1)
			{
				// 遍历每个可能的位置
				isinit = false;                 // 如果有，那么就不是刚刚开局
				int nowcolor = BOX[i][j].color_val; // 现在遍历到的颜色
				int length[4] = { 0,0,0,0 };    // 四个方向的长度
				for (int k = 0; k < 4; k++)
				{
					// 原理同寻找最佳位置
					int nowi = i;
					int nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].color_val == nowcolor)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					nowi = i;
					nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].color_val == 1 - nowcolor)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
				}
				for (int k = 0; k < 4; k++)
				{
					if (length[k] >= 5) {
						// 如果满五子
						if (nowcolor == playercolor)
						{
							win = playercolor; // 玩家胜
						}
						if (nowcolor == 1 - playercolor)
						{
							win = 1 - playercolor; // 电脑胜
						}
					}
				}
				//if ((!isinit) && findbestseat1(playercolor).number == 0 && findbestseat1(1 - playercolor).number == 0)
				//{
				//	// 如果不是开局且双方无最佳位置
				//	win = 2; // 平局
				//}
			}
		}
	}
}

// 游戏主函数
void game()
{
	bool new_game = true;
	// 上一个鼠标停的坐标
	int oldi = 0;
	int oldj = 0;
	// 随机化玩家颜色
	srand(time(NULL));
	playercolor = rand() % 2;
	// 绘制背景
	setfillcolor(RGB(255, 205, 150));
	solidrectangle(40, 25, 515, 500);
	// 设置字体样式
	settextstyle(30, 15, 0, 0, 0, 1000, false, false, false);
	settextcolor(CYAN);
	// 输出标示语
	if (playercolor == 0)
	{
		outtextxy(75, 500, _T("玩家执白后行，电脑执黑先行"));
		whoplay = 1;
	}
	else
	{
		outtextxy(75, 500, _T("玩家执黑先行，电脑执白后行"));
		whoplay = 0;
	}
	draw(); // 绘制
	while (1)
	{
	NEXTPLAYER:
		if (whoplay == 0)
		{
			// 玩家下棋
			MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					if (mouse.x > BOX[i][j].x && mouse.x<BOX[i][j].x + 30//判断x坐标
						&& mouse.y>BOX[i][j].y && mouse.y < BOX[i][j].y + 30//判断y坐标
						&& BOX[i][j].color_val == -1)//判断是否是空位置
					{
						// 如果停在某一个空位置上面
						if (mouse.mkLButton)
						{
							// 如果按下了
							BOX[i][j].color_val = playercolor; // 下棋
							set_neighbor(i, j, ADD_NEIGHBOR);
							BOX[i][j].isnew = true;        // 新位置更新
							oldi = -1;
							oldj = -1;
							// 下一个玩家
							whoplay = 1;
							goto DRAW;
						}
						// 更新选择框
						BOX[oldi][oldj].isnew = false;
						BOX[oldi][oldj].draw();
						BOX[i][j].isnew = true;
						BOX[i][j].draw();
						oldi = i;
						oldj = j;
					}
				}
			}
		}
		else
		{
			// 电脑下棋
			seat best;
			best = findbestseat2(1 - playercolor); // 寻找最佳位置
			if (new_game)
			{
				// 开局情况
				int drawi = 7;
				int drawj = 7;
				while (BOX[drawi][drawj].color_val != -1)
				{
					drawi--;
					drawj++;
				}
				set_neighbor(drawi, drawj, ADD_NEIGHBOR);
				BOX[drawi][drawj].color_val = 1 - playercolor;
				BOX[drawi][drawj].isnew = true;
				new_game = false;
			}
			else
			{
				BOX[best.i][best.j].color_val = 1 - playercolor;//下在最佳位置
				set_neighbor(best.i, best.j, ADD_NEIGHBOR);
				BOX[best.i][best.j].isnew = true;
			}
			whoplay = 0;
			goto DRAW; // 轮到下一个
		}
	}
DRAW: // 绘制
	isWIN(); // 检测输赢
	draw();
	if (win == -1)
	{
		// 如果没有人胜利
		Sleep(500);
		goto NEXTPLAYER; // 前往下一个玩家
	}
	// 胜利处理
	settextcolor(RGB(0, 255, 0));
	Sleep(1000);
	if (win == 0)
	{
		outtextxy(255, 255, _T("白胜"));
	}
	if (win == 1)
	{
		outtextxy(255, 255, _T("黑胜"));
	}
	if (win == 2)
	{
		outtextxy(255, 255, _T("平局"));
	}
	// 给反应时间
	Sleep(5000);
	return;
}
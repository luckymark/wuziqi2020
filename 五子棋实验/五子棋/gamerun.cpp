#include <stdio.h>
#include <graphics.h>
#include <Windows.h>
#include "draw.h"
#include "GameManagement.h"
#include "AI.h"
void gamerun();
int Chess_status[15][15] = {0};//1表示黑子，2表示白子，0表示没有棋子


void gamerun()
{
	IMAGE img = NULL;
	int olds_chess[15][15] = { 0 };
	int x, y;
	int i=0;//计数器(记步数如果i等于225则判断为和棋)
	MOUSEMSG m;
	memset(Chess_status, 0 * 0, sizeof(Chess_status));         //清空数组，释放前一局的数据
	Draw_board();
	while (1)
	{
		if (i % 2 == 0)
		{
			if (MouseHit())
			{
				m = GetMouseMsg();//获取鼠标信息
				FlushMouseMsgBuffer();
				if (m.uMsg == WM_LBUTTONDOWN)//判断是否点击右键
				{
					x = m.x / 40;
					y = m.y / 40;

					i++;
					Draw_Circle(x ,y , BLACK);
					HeQi(i);
					Chess_status[x][y] = 1;
					if (i == 225)                     //判断棋盘是否画满
					{
						break;
					}	
					if (ResultCheck(x, y, i,Chess_status))      //根据*检查结果*函数体的返回值，输出结果
					{
						RECT r = { 0, 0, 639, 479 };
						drawtext(_T("黑棋获胜"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					if (m.x <= 770 && m.x >= 620 && m.y <= 345 && m.y >= 300)    //“重新开始”
					{
						memset(Chess_status, 0 * 0, sizeof(Chess_status));
						gamerun();
					}
					if (m.x <= 770 && m.x >= 620 && m.y <= 490 && m.y >= 450)    //“退出游戏”
					{
						exit(0);
					}
				}
				
			}
		}
		else if(i % 2 != 0)
		{
			i++;
			pos best_pos = AI(Chess_status,olds_chess);
			Draw_Circle(best_pos.pos_x, best_pos.pos_y, WHITE);
			HeQi(i);
			Chess_status[best_pos.pos_x][best_pos.pos_y] = 2;
			if (ResultCheck(best_pos.pos_x, best_pos.pos_y, i, Chess_status))      //根据*检查结果*函数体的返回值，输出结果
			{
				RECT r = { 0, 0, 639, 479 };
				drawtext(_T("白棋获胜"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
		}
	}
}
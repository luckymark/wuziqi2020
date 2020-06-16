#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gamerun.h"

struct pos
{
	int pox_x = 0;
	int pos_y = 0;
};

pos AI(const int chess[15][15], int olds_chess[15][15]);
void CheeseStatistics(const int olds_chess[15][15], int cheese[15][15][8][2]);
void Score(const int status[15][15], int cheese[15][15][8][2], int score1[15][15], int score2[15][15]);

pos AI(const int chess[15][15], int olds_chess[15][15])
{
	int i, j;
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	int cheese[15][15][8][2] = { 0 };
	int score1[15][15] = { 0 };
	int score2[15][15] = { 0 };
	for (i = 0; i <= 14; i++)         //行
		for (j = 0; j <= 14; j++)     //列
		{
			olds_chess[i][j] = chess[i][j];
		}
	CheeseStatistics(olds_chess, cheese);
	Score(chess,cheese, score1, score2);
	for (i = 0; i <= 14; i++)         //行
		for (j = 0; j <= 14; j++)     //列
		{
			if (score1[x1][y1] < score1[i][j])    //找出棋盘上对黑棋分数最高的空位
			{
				x1 = i;
				y1 = j;
			}
		}
	for (i = 0; i <= 14; i++)         //行
		for (j = 0; j <= 14; j++)     //列
		{
			if (score2[x2][y2] < score2[i][j])    //找出棋盘上对白棋分数最高的空位
			{
				x2 = i;
				y2 = j;
			}
		}
	if (score1[x1][y1] > score2[x2][y2])          //比较黑棋和白棋空位分数大小，选择是该进攻还是防守
	{

		return { x1,y1 };
	}
	else
	{
		
		return { x2,y2 };

	}
}

void CheeseStatistics(const int olds_chess[15][15], int cheese[15][15][8][2])
{
	int i, j, k, t, count;
	int t_x, t_y;
	int dx[8] = { 0,1,1,1,0,-1,-1,-1 };
	int dy[8] = { -1,-1,0,1,1,1,0,-1 };
	for (i = 0; i <= 14; i++)         //行判断
		for (j = 0; j <= 14; j++)     //列判断
			if (olds_chess[i][j] == 0)//判断该位置是否有棋子
			{
				for (k = 0; k < 8; k++)
				{
					count = 0;
					t_x = i; t_y = j;
					for (t = 0; t < 5; t++)//最多判断五个连子
					{
						t_x += dx[k];
						t_y += dy[k];
						if (t_x > 15 || t_x < 1 || t_y > 15 || t_y < 1)//限制在棋盘内
							break;
						if (olds_chess[t_x][t_y] == 1)//计算某一方向黑棋个数
							count++;
						else
							break;   //判断是否为连续同一颜色棋子，不同则退出统计
					}
					cheese[i][j][k][0] = count;
					count = 0;
					t_x = i; t_y = j;
					for (t = 0; t < 5; t++)
					{
						t_x += dx[k];
						t_y += dy[k];
						if (t_x > 15 || t_x < 1 || t_y > 15 || t_y < 1)
							break;
						if (olds_chess[t_x][t_y] == 2)//判断白棋个数
							count++;
						else
							break;
					}
					cheese[i][j][k][1] = count;
				}
			}
}

void Score(const int status[15][15], int cheese[15][15][8][2], int score1[15][15], int score2[15][15])
{
	int i, j, k;
	int score;
	for (i = 0; i <= 14; i++)         //行
		for (j = 0; j <= 14; j++)     //列
		{
			if (status[i][j] == 0)
			{
				score = 0;
				for (k = 0; k < 4; k++)
				{
					if (cheese[i][j][k][0] + cheese[i][j][k + 4][0] >= 4)
						score += 10000;
					else if (cheese[i][j][k][0] + cheese[i][j][k + 4][0] == 3)
						score += 1000;
					else if (cheese[i][j][k][0] + cheese[i][j][k + 4][0] == 2)
						score += 100;
					else if (cheese[i][j][k][0] + cheese[i][j][k + 4][0] == 1)
						score += 10;
				}
				score1[i][j] = score;           //当前空位对黑棋的分数
				score = 0;
				for (k = 0; k < 4; k++)
				{
					if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] >= 4)
						score += 10000;
					else if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] == 3)
						score += 1000;
					else if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] == 2)
						score += 100;
					else if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] == 1)
						score += 10;
				}
				score2[i][j] = score;          //当前位置对白棋的分数
			}
		}
}
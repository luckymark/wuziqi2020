#include"data.h"
extern int board[16][16];
extern int dir[4][2];

bool outboard(int x, int y)//判断位置(x,y)是否在棋盘外,是则返回真
{
	return x < 1 || x > 15 || y < 1 || y > 15;
}

int evaluateP(int x, int y, int color)
{
	int five = 0, alive3 = 0, alive4 = 0, die3 = 0, die4 = 0, alive2 = 0, die2 = 0, leftmax = 4, rightmax = 4;
	int oppcolor = 3 - color;
	for (int dircount = 0; dircount < 4; dircount++)//4个方向
	{
		int leftcnt = 0, rightcnt = 0, totlen;
		int leftx = x, lefty = y;
		while (!outboard(leftx - dir[dircount][0], lefty - dir[dircount][1]) &&
			board[leftx - dir[dircount][0]][lefty - dir[dircount][1]] == color)
		{
			leftx -= dir[dircount][0];
			lefty -= dir[dircount][1];
			leftcnt++;
		}
		int rightx = x, righty = y;
		while (!outboard(rightx + dir[dircount][0], righty + dir[dircount][1]) &&
			board[rightx + dir[dircount][0]][righty + dir[dircount][1]] == color)
		{
			rightx += dir[dircount][0];
			righty += dir[dircount][1];
			rightcnt++;
		}
		totlen = leftcnt + rightcnt + 1;//在当前方向上组成的连续棋子的长度
		int colorleft[5], colorright[5];
		for (int i = 1; i <= 4; i++)
		{
			if (!outboard(leftx - i * dir[dircount][0], lefty - i * dir[dircount][1]))
				colorleft[i] = board[leftx - i * dir[dircount][0]][lefty - i * dir[dircount][1]];
			else if (leftmax > i - 1)
				leftmax = i - 1;
			if (!outboard(rightx + i * dir[dircount][0], righty + i * dir[dircount][1]))
				colorright[i] = board[rightx + i * dir[dircount][0]][righty + i * dir[dircount][1]];
			else if (rightmax > i - 1)
				rightmax = i - 1;
		}
		if (totlen >= 5)
		{
			five++;
		}
		else if (totlen == 4)
		{
			if (leftmax >= 1 && rightmax >= 1 && colorleft[1] == Empty && colorright[1] == Empty)
				alive4++;
			else if (leftmax >= 1 && colorleft[1] == Empty || rightmax >= 1 && colorright[1] == Empty)
				die4++;
		}
		else if (totlen == 3)
		{
			if (leftmax >= 1 && rightmax >= 1 && colorleft[1] == Empty && colorright[1] == Empty)
			{
				if (leftmax >= 2 && rightmax >= 2 && colorleft[2] == color && colorright[2] == color)
					die4 += 2;
				else if (leftmax >= 2 && colorleft[2] == color || rightmax >= 2 && colorright[2] == color)
					die4++;
				else if (leftmax >= 2 && colorleft[2] == Empty || rightmax >= 2 && colorright[2] == Empty)
					alive3++;
				else die3++;
			}
			else if (leftmax >= 1 && colorleft[1] == Empty)
			{
				if (leftmax >= 2 && colorleft[2] == color)
					die4++;
				else if (leftmax >= 2 && colorleft[2] == Empty)
					die3++;
			}
			else if (rightmax >= 1 && colorright[1] == Empty)
			{
				if (rightmax >= 2 && colorright[2] == color)
					die4++;
				else if (rightmax >= 2 && colorright[2] == Empty)
					die3++;
			}
		}
		else if (totlen == 2)
		{
			if (leftmax >= 1 && rightmax >= 1 && colorleft[1] == Empty && colorright[1] == Empty)
			{
				if (leftmax == 1 && rightmax == 1 || leftmax == 1 && rightmax >= 2 && colorright[2] == oppcolor ||
					rightmax == 1 && leftmax >= 2 && colorleft[2] == oppcolor ||
					leftmax >= 2 && rightmax >= 2 && colorleft[2] == oppcolor && colorright[2] == oppcolor)
					continue;
				if (leftmax >= 3 && rightmax >= 3 && colorleft[2] == color && colorleft[3] == color &&
					colorright[2] == color && colorright[3] == color)
					die4 += 2;
				else if (leftmax >= 3 && colorleft[2] == color && colorleft[3] == color ||
					rightmax >= 3 && colorright[2] == color && colorright[3] == color)
					die4++;
				else if (leftmax >= 3 && colorleft[2] == color && colorleft[3] == Empty ||
					rightmax >= 3 && colorright[2] == color && colorright[3] == Empty)
					alive3++;
				else if (leftmax >= 3 && colorleft[2] == color && colorleft[3] == oppcolor ||
					leftmax == 2 && colorleft[2] == color || rightmax == 2 && colorright[2] == color ||
					rightmax >= 3 && colorright[2] == color && colorright[3] == oppcolor)
					die3++;
				else if (leftmax >= 3 && colorleft[2] == Empty && colorleft[3] == color ||
					rightmax >= 3 && colorright[2] == Empty && colorright[3] == color)
					die3++;
				else if (leftmax >= 2 && rightmax >= 2 && colorleft[2] == Empty && colorright[2] == Empty)
					alive2++;
				else if (leftmax >= 2 && colorleft[2] == Empty || rightmax >= 2 && colorright[2] == Empty)
					die2++;
			}
			else if (leftmax >= 1 && colorleft[1] == Empty)
			{
				if (leftmax < 3 || colorleft[2] == oppcolor || colorleft[3] == oppcolor)
					continue;
				if (colorleft[2] == color && colorleft[3] == color)
					die4++;
				else if (colorleft[2] == color || colorleft[3] == color)
					die3++;
				else die2++;
			}
			else if (rightmax >= 1 && colorright[1] == Empty)
			{
				if (rightmax < 3 || colorright[2] == oppcolor || colorright[3] == oppcolor)
					continue;
				if (colorright[2] == color && colorright[3] == color)
					die4++;
				else if (colorright[2] == color || colorright[3] == color)
					die3++;
				else die2++;
			}
		}
		else
		{
			if (leftmax >= 1 && rightmax >= 1 && colorleft[1] == Empty && colorright[1] == Empty)
			{
				if ((leftmax < 2 || colorleft[2] == oppcolor) &&
					(rightmax < 3 || colorright[2] == oppcolor || colorright[3] == oppcolor) ||
					(leftmax == 2 || colorleft[3] == oppcolor) && (rightmax < 2 || colorright[2] == oppcolor))
					continue;
				if (leftmax >= 4 && rightmax >= 4 &&
					colorleft[2] == color && colorleft[3] == color && colorleft[4] == color &&
					colorright[2] == color && colorright[3] == color && colorright[4] == color)
					die4 += 2;
				else if (leftmax >= 4 && colorleft[2] == color && colorleft[3] == color && colorleft[4] == color ||
					rightmax >= 4 && colorright[2] == color && colorright[3] == color && colorright[4] == color)
					die4++;
				else if (leftmax >= 4 && colorleft[2] == color && colorleft[3] == color && colorleft[4] == Empty ||
					rightmax >= 4 && colorright[2] == color && colorright[3] == color && colorright[4] == Empty)
					alive3++;
				else if (leftmax == 3 && colorleft[2] == color && colorleft[3] == color ||
					leftmax >= 4 && colorleft[2] == color && colorleft[3] == color && colorleft[4] == oppcolor ||
					leftmax >= 4 && colorleft[3] == color && colorleft[4] == color && colorleft[2] == Empty ||
					leftmax >= 4 && colorleft[2] == color && colorleft[4] == color && colorleft[3] == Empty ||
					rightmax == 3 && colorright[2] == color && colorright[3] == color ||
					rightmax >= 4 && colorright[2] == color && colorright[3] == color && colorright[4] == oppcolor ||
					rightmax >= 4 && colorright[3] == color && colorright[4] == color && colorright[2] == Empty ||
					rightmax >= 4 && colorright[2] == color && colorright[4] == color && colorright[3] == Empty)
					die3++;
				else if (leftmax >= 2 && rightmax >= 2 && colorleft[2] == color && colorright[2] == color)
					die3++;
				else if (leftmax >= 3 && colorleft[2] == color && colorleft[3] == Empty ||
					rightmax >= 3 && colorright[2] == color && colorright[3] == Empty)
					alive2++;
				else if (leftmax >= 4 && colorleft[2] == Empty && colorleft[3] == color && colorleft[4] == Empty ||
					rightmax >= 4 && colorright[2] == Empty && colorright[3] == color && colorright[4] == Empty)
					alive2++;
				else if (leftmax >= 2 && colorleft[2] == color || leftmax >= 3 && colorleft[3] == color ||
					leftmax >= 4 && colorleft[4] == color || rightmax >= 2 && colorright[2] == color ||
					rightmax >= 3 && colorright[3] == color || rightmax >= 4 && colorright[4] == color)
					die2++;
			}
			else if (leftmax >= 1 && colorleft[1] == Empty)
			{
				if (leftmax < 4 || colorleft[2] == oppcolor || colorleft[3] == oppcolor || colorleft[4] == oppcolor)
					continue;
				if (colorleft[2] == color && colorleft[3] == color && colorleft[4] == color)
					die4++;
				else if (colorleft[2] == color && colorleft[3] == color ||
					colorleft[3] == color && colorleft[4] == color ||
					colorleft[2] == color && colorleft[4] == color)
					die3++;
				else if (colorleft[2] == color || colorleft[3] == color || colorleft[4] == color)
					die2++;
			}
			else if (rightmax >= 1 && colorright[1] == Empty)
			{
				if (rightmax < 4 || colorright[2] == oppcolor || colorright[3] == oppcolor || colorright[4] == oppcolor)
					continue;
				if (colorright[2] == color && colorright[3] == color && colorright[4] == color)
					die4++;
				else if (colorright[2] == color && colorright[3] == color ||
					colorright[3] == color && colorright[4] == color ||
					colorright[2] == color && colorright[4] == color)
					die3++;
				else if (colorright[2] == color || colorright[3] == color || colorright[4] == color)
					die2++;
			}
		}
	}
	if (five && color == Black) return 10000000;
	if (five && color == White) return 4500000;
	if (alive4 || die4 >= 2 || die4 && alive3) return 200000;
	if (alive3 >= 2) return 20000;
	if (die4 && die3 || alive3 && die3) return 1000;
	if (die4) return 500;
	if (alive3) return 250;
	if (alive2 >= 2) return 100;
	if (alive2) return 30;
	if (die3) return 20;
	if (die2) return 2;
	return 1;
}
Point evaluatePoint(int x, int y)//计算一个点的搜索优先级，以便进行α-β剪枝
{
	int scoreb = evaluateP(x, y, Black);
	int scorew = evaluateP(x, y, White);
	Point p;
	p.x = x; p.y = y;
	p.score = scoreb + scorew;
	return p;
}
Point evaluateWhole(int x, int y)//计算整个棋面的分数
{
	int totBlack = 0, totWhite = 0;
	for (int i = 1; i <= 15; i++)
		for (int j = 1; j <= 15; j++)
		{
			if (board[i][j] == Black)
				totBlack += evaluateP(i, j, Black);
			if (board[i][j] == White)
				totWhite += evaluateP(i, j, White);
		}
	Point ret;
	ret.x = x; ret.y = y; ret.score = totBlack - totWhite;
	return ret;
}
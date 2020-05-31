#include "location.h"
#include<algorithm>
using namespace std;
struct loca
{
	int x, y, point;
}Loca[400];
int totLoca;
int mx[8][2] = { {1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1} };
int ev(int x, int y,int map[][MAXN],int origal)
{
	int x1;
	int y1 ,x2,y2;
	int ans = 1;
	int maxxsame = 1,maxxdif=1;
	int color = 0,lo;
	int i = 0;
	while(i<8)
	{
		x1 = x+ mx[i][0], y1 = y+ mx[i][1];
		x2 = x + mx[i + 1][0], y2 = y + mx[i + 1][1];
		color = map[x1][y1];
		lo = map[x2][y2];
		ans = 0;
		if (color == lo && i%2==0 && color!=0)
		{
			x1 = x, y1 = y;
			while (1)
			{
				x1 = x1 + mx[i][0];
				y1 = y1 + mx[i][1];
				if (x1 >= 1 && y1 >= 1 && x1 < MAXN - 1 && y1 < MAXN - 1 && map[x1][y1] == color)  ans++;
				else  break;
			}
			x1 = x, y1 = y;
			while (1)
			{
				x1 = x1 + mx[i+1][0];
				y1 = y1 + mx[i+1][1];
				if (x1 >= 1 && y1 >= 1 && x1 < MAXN - 1 && y1 < MAXN - 1 && map[x1][y1] == color)  ans++;
				else  break;
			}
			if (color == origal)  maxxsame = max(maxxsame, ans + 1);
			else   maxxdif = max(maxxdif, ans);
			
			i = i + 2;

		}
		else
		{
			ans = 1;
			if (color == 0)
			{
				i++;
				continue;
			}
			while (1)
			{
				x1 = x1 + mx[i][0];
				y1 = y1 + mx[i][1];
				if (x1 >= 1 && y1 >= 1 && x1 < MAXN - 1 && y1 < MAXN - 1 && map[x1][y1] == color)  ans++;
				else  break;
			}
			if (color == origal)
			{
				if (ans + 1 > maxxsame)  maxxsame = ans + 1;
			}
			else
			{
				if (ans > maxxdif)  maxxdif = ans;
			}
			i++;
		}
	}
	if (maxxsame == 5)  return 7;
	if (maxxdif == 4)  return 6;
	if (maxxsame == 4)   return 5;
	if (maxxdif == 3)   return 4;
	if (maxxsame == 1)   return maxxdif;
	return maxxsame;
	/*for (int i = 0;i < 8;i++)
	{
		x1 = x, y1 = y;
		ans = 1;
		x1 = x1 + mx[i][0];
		y1 = y1 + mx[i][1];
		color = map[x1][y1];
		if (color == 0)  continue;
		while (1)
		{
			x1 = x1 + mx[i][0];
			y1 = y1 + mx[i][1];
			if (x1 >= 1 && y1 >= 1 && x1 < MAXN - 1 && y1 < MAXN - 1 && map[x1][y1] == color)  ans++;
			else  break;
		}
		if (color != origal)
		{
			if (ans == 3)  ans = 3;
			if (ans == 4)    ans = 6;
		}
		if (color == origal)
		{
			ans++;
			if (ans == 5)   ans = 7;
			if (ans == 4)   ans = 5;
			if (ans == 3) ans = 4;
		}
		if (ans > maxx)  maxx = ans;
	}
	return maxx;*/
}
int coo(struct loca x, struct loca y)
{
	if (x.point > y.point)  return 1;
	return 0;
}
void Getlocation(int map[][MAXN],int color)
{
	totLoca = 0;
	int x, y;
	for (int i = 1;i <= MAXN-2;i++)
	{
		for (int j = 1;j <= MAXN - 2;j++)
		{
			if (!map[i][j])
			{
				for (int p = 0;p < 8;p++)
				{
					x = i + mx[p][0];
					y = j + mx[p][1];
					if (x >= 1 && y >= 1 && x < MAXN - 1 && y < MAXN - 1 && map[x][y])
					{
						Loca[++totLoca].x = i;
						Loca[totLoca].y = j;
						Loca[totLoca].point = ev(i, j,map,color);
					}
				}
			}
		}
	}
	sort(Loca + 1, Loca + totLoca + 1, coo);
	if (Loca[1].point == 5 || Loca[1].point == 6 || Loca[1].point==7 || Loca[1].point==4)   totLoca = 1;
}
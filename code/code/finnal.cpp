#include "define_var.h"
#include "finnal.h"

int mx[8][2] = { {1,0},{-1,0},{1,-1},{-1,-1},{1,1},{-1,1},{0,1},{0,-1} };

int Legal(int x, int y)
{
	if (x<1 || y<1 || x>MAXN - 2 || y>MAXN - 2)  return 0;
	return 1;
}
int Won(int map[][MAXN])
{
	int x, y,now;
	for (int i = 1;i <= MAXN-2;i++)
	{
		for (int j = 1;j <= MAXN - 2;j++)
		{
			if (map[i][j])
			{
				x = i, y = j;
				for (int k = 0;k < 8;k++)
				{
					x = i, y = j,now=0;
					while (Legal(x, y) && map[x][y] == map[i][j])
					{
						now++;
						x = x + mx[k][0];y = y + mx[k][1];
						if (now == 5)  break;
					}
					if (now == 5)  return map[i][j];
				}
			}
		}
	}
	return 0;
}
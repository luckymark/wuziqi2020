#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include"wuziqi.h"

extern int chess[16][16];
extern int computerx, computery;

int score(int a, int map[16][16], int n)
{
	int sum = 0;
	int k = 0;
	for (int i = 1; i <= 15; i++)								// 判断活一
	{
		for (int j = 1; j <= 15; j++)
		{
			if (map[i][j] == a && i > 1 && i < 15 && j>1 && j < 15)
			{
				if (map[i - 1][j - 1] + map[i - 1][j] + map[i - 1][j + 1] + map[i][j - 1]\
					+ map[i][j + 1] + map[i + 1][j - 1] + map[i + 1][j] + map[i + 1][j + 1] == 0)
				{
					sum += 10;
				}
			}
		}
	}

	for (int i = 1; i < 15; i++)								// 判断横行
	{
		k = 0;
		for (int j = 1; j <= 15; j++)
		{
			if (map[i][j] == a)
				k++;
			else
				k = 0;
			if (k > 1 && (j == 15 || map[i][j + 1] != a))
			{
				if (j != k && map[i][j - k] == 0 && j != 15 && map[i][j + 1] == 0)
				{
					sum += pow(10, k);
				}
				else if ((j != k && map[i][j - k] == 0) || (j != 15 && map[i][j + 1] == 0))
				{
					if (k == 5)
						sum += 100000;
					else
						sum += pow(10, k) / 10;
				}
				else
				{
					if (k == 5)
						sum += 100000;
				}
				k = 0;
			}
		}
	}

	for (int i = 1; i < 15; i++)								// 判断纵行
	{
		k = 0;
		for (int j = 1; j <= 15; j++)
		{
			if (map[j][i] == a)
				k++;
			else
				k = 0;
			if (k > 1 && (j == 15 || map[j + 1][i] != a))
			{
				if (j != k && map[j - k][i] == 0 && j != 15 && map[j + 1][i] == 0)
				{
					sum += pow(10, k);
				}
				else if ((j != k && map[j - k][i] == 0) || (j != 15 && map[j + 1][i] == 0))
				{
					if (k == 5)
						sum += 100000;
					else
						sum += pow(10, k) / 10;
				}
				else
				{
					if (k == 5)
						sum += 100000;
				}
				k = 0;
			}
		}
	}

	for (int i = 1; i <= 11; i++)								// 判断下半部分的\方向
	{
		k = 0;
		int j = 0;
		while (i + j <= 15)
		{
			if (map[i + j][1 + j] == a)
				k++;
			else
				k = 0;
			if (k > 1 && (j == 15 - i || map[i + j + 1][1 + j + 1] != a))
			{
				if (j != k - 1 && map[i + j - k][1 + j - k] == 0 && j != 15 - i && map[i + j + 1][1 + j + 1] == 0)
				{
					sum += pow(10, k);
				}
				else if ((j != k - 1 && map[i + j - k][1 + j - k] == 0) || (j != 15 - i && map[i + j + 1][1 + j + 1] == 0))
				{
					if (k == 5)
						sum += 1000000;
					else
						sum += pow(10, k) / 10;
				}
				else
				{
					if (k == 5)
						sum += 1000000;
				}
				k = 0;
			}
			j++;
		}
	}

	for (int i = 2; i <= 11; i++)								//判断上半部分的\方向
	{
		k = 0;
		int j = 0;
		while (i + j <= 15)
		{
			if (map[1 + j][i + j] == a)
				k++;
			else
				k = 0;
			if (k > 1 && (j == 15 - i || map[1 + j + 1][i + j + 1] != a))
			{
				if (j != k - 1 && map[1 + j - k][i + j - k] == 0 && j != 15 - i && map[1 + j + 1][i + j + 1] == 0)
				{
					sum += pow(10, k);
				}
				else if ((j != k - 1 && map[1 + j - k][i + j - k] == 0) || (j != 15 - i && map[1 + j + 1][i + j + 1] == 0))
				{
					if (k == 5)
						sum += 100000;
					else
						sum += pow(10, k) / 10;
				}
				else
				{
					if (k == 5)
						sum += 100000;
				}
				k = 0;
			}
			j++;
		}
	}

	for (int i = 5; i <= 15; i++)
	{
		k = 0;
		int j = 0;
		while (i - j >= 1)
		{
			if (map[i - j][1 + j] == a)
				k++;
			else
				k = 0;
			if (k > 1 && (i - j == 1 || map[i - j - 1][1 + j + 1] != a))
			{
				if (j != k - 1 && map[i - j + k][j - k] == 0 && i - j != 1 && map[i - j - 1][1 + j + 1] == 0)
				{
					sum += pow(10, k);
				}
				else if ((j != k - 1 && map[i - j + k][j - k] == 0) || (i - j != 1 && map[i - j - 1][1 + j + 1] == 0))
				{
					if (k == 5)
						sum += 100000;
					else
						sum += pow(10, k) / 10;
				}
				else
				{
					if (k == 5)
						sum += 100000;
				}
			}
			j++;
		}
	}

	for (int i = 2; i <= 11; i++)
	{
		k = 0;
		int j = 0;
		while (i + j <= 15)
		{
			if (map[i + j][15 - j] == a)
				k++;
			else
				k = 0;
			if (k > 1 && (i + j == 15 || map[i + j + 1][15 - j - 1] != a))
			{
				if (j != k - 1 && map[i + j - k][15 - j + k] == 0 && i + j != 15 && map[i + j + 1][15 - j - 1] == 0)
					sum += pow(10, k);
				else if ((j != k - 1 && map[i + j - k][15 - j + k] == 0) || (i + j != 15 && map[i + j + 1][15 - j - 1] == 0))
				{
					if (k == 5)
						sum += 100000;
					else
						sum += pow(10, k - 1.0);
				}
				else
				{
					if (k == 5)
						sum += 100000;
				}
			}
			j++;
		}
	}

	if (n == 1)
	{
//printf("%d \n", sum);
return sum;
	}
	else
	{
	//printf("%d ", sum);
	return sum - score(1, map, 1);
	}
}

bool judge(int x, int y, int map[16][16])
{
	int i, j;
	for (i = x - 1; i <= x + 1; i++)
		for (j = y - 1; j <= y + 1; j++)
			if ((i > 0 && j > 0 && i < 16 && j < 16) && (map[i][j] == 1 || map[i][j] == 2))
				return 1;
	/*for (i = x - 2; i <= x + 2; i += 2)
		for (j = y - 2; j <= y + 2; j += 2)
			if ((i > 0 && j > 0 && i < 16 && j < 16) && (map[i][j] == 1 || map[i][j] == 2))
				return 1;*/
	return 0;
}

int maxmin(int map[16][16], int deep, int Alpha, int Beta)
{
	int val;
	int temp[16][16];
	if (deep == 0)
	{
		return score(2, map, 2);
	}
	else if (deep % 2 == 0)
	{
		for (int i = 1; i <= 15; i++)
		{
			for (int j = 1; j <= 15; j++)
			{
				if (map[i][j] == 0 && judge(i,j,map))
				{
					memcpy(temp, map, sizeof(int) * 256);
					temp[i][j] = 2;
					//printf("%d %d ", i, j);
					if (win(i, j, temp))
					{
						//printf("win!");
						computerx = i;
						computery = j;
							return score(2, temp, 2);
						}
						val = maxmin(temp, deep - 1, Alpha, Beta);
						if (val > Alpha)
						{
							if (deep == DEPTH)
							{
								computerx = i;
								computery = j;
							}
							//printf("\ndeep: %d %d %d %d\n", deep, i, j, val);
							Alpha = val;
						}
						if (Alpha > Beta)
							return Alpha;
					}
				}
			}
		//}
		return Alpha;
	}
	else
	{
		for (int i = 1; i <= 15; i++)
		{
			for (int j = 1; j <= 15; j++)
			{
				if (map[i][j] == 0 && judge(i, j, map))
				{
					memcpy(temp, map, sizeof(int) * 256);
					temp[i][j] = 1;
					//printf("%d %d ", i, j);
					if (win(i, j, temp))
					{
						//printf("lose!");
						return score(2, temp, 2);
					}
					val = maxmin(temp, deep - 1, Alpha, Beta);
					if (val < Beta)
					{
						Beta = val;
						//printf("\ndeep: %d %d %d %d\n", deep, i, j, val);
					}
					if (Alpha > Beta)
						return Beta;
				}
			}
		}
		return Beta;
	}
}

int judge2(int i, int j,int map[16][16],int n)
{
	int kkk[16][16];
	int m;
	if (n == 1)
		m = 2;
	else
		m = 1;
	memcpy(kkk, map, 256 * sizeof(int));
	kkk[i][j] = n;
	if (win(i, j, kkk))
		return 5;
	if (four(i, j, kkk))
		return 3;
	kkk[i][j] = m;
	if (win(i, j, kkk))
		return 4;
	if (four(i, j, kkk))
		return 2;
	return 0;
}

bool four(int x, int y, int map[16][16])					// 判断是否生成活四
{
	int a = map[x][y];
	if (a == 0)
		return 0;
	int i, j, sum = 0, flag = 0;
	for (i = max(1, x - 4), sum = 0; i <= min(15, x + 4); i++)					// 在竖行判断
	{
		if (flag == 0)
		{
			if (map[i][y] == 0)
				flag = 1;
		}
		else
		{
			if (sum == 4 && map[i][y] == 0)
			{
				sum++;
				break;
			}
			else if (map[i][y] != a)
			{
				sum = 0;
				flag = 0;
			}
			else
				sum++;
		}
	}
	if (sum == 5)
		return 1;
	for (j = max(1, y - 4), sum = 0, flag = 0; j <= min(15, y + 4); j++)				// 横行判断
	{
		if (flag == 0)
		{
			if (map[x][j] == 0)
				flag = 1;
		}
		else
		{
			if (sum == 4 && map[x][j] == 0)
			{
				sum++;
				break;
			}
			else if (map[x][j] != a)
			{
				sum = 0;
				flag = 0;
			}
			else
			{
				sum++;
			}
		}
	}
	if (sum == 5)
		return 1;
	for (sum = 0, i = x - 4, j = y - 4, flag = 0; i <= x + 4 && j <= y + 4; i++, j++)	// 斜行判断
	{
		if (i < 1 || i>15 || j < 1 || j>15)
			continue;
		if (flag == 0)
		{
			if (map[i][j] == 0)
				flag = 1;
		}
		else
		{
			if (sum == 4 && map[i][j] == 0)
			{
				sum++;
				break;
			}
			else if (map[i][j] != a)
			{
				sum = 0;
				flag = 0;
			}
			else
				sum++;
		}
	}
	if (sum == 5)
		return 1;
	for (sum = 0, i = x - 4, j = y + 4, flag = 0; i <= x + 4 && j >= y - 4; i++, j--)	// 斜行判断
	{
		if (i < 1 || i>15 || j < 1 || j>15)
			continue;
		if (flag == 0)
		{
			if (map[i][j] == 0)
				flag = 1;
		}
		else
		{
			if (sum == 4 && map[i][j] == 0)
			{
				sum++;
				break;
			}
			else if (map[i][j] != a)
			{
				sum = 0;
				flag = 0;
			}
			else
				sum++;
		}
	}
	if (sum == 5)
		return 1;
	return 0;
}
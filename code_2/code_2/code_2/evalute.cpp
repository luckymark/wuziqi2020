#include "finnal.h"
#include "board.h"
#include<iostream>
using namespace std;

extern struct data
{
	int x, y;
}lines[9][MAXN * 3][MAXN * 3];
extern int NumLines[9][MAXN * 3];
extern int totLines[9];
int point[6] = { 0,10,100,1000,100000,10000000 };

int calc_point(int map[][MAXN])
{
	int x, y;
    int now = 0, squ = 0, xs, ys;
    int pointp[3] = { 0,0,0 };
    for (int p = 0;p < 4;p++)
    {
        for (int i = 1;i <= totLines[p];i++)
        {
            now = 0;squ = 0;
            xs = -1, ys = -1;
            for (int j = 1;j <= NumLines[p][i];j++)
            {
                x = lines[p][i][j].x;
                y = lines[p][i][j].y;
                if (map[x][y] == 0)
                {
                    if (now > 0)
                    {
                        if ((xs==-1 && ys==-1) || map[xs][ys]==3-now)  squ--;
                        pointp[now] += point[squ];
                        now = 0, squ = 0;
                        xs = 0, ys = 0;
                    }
                }
                if (map[x][y] == 1)
                {
                    if (now == map[x][y])  squ++;
                    if (now == 0)
                    {
                        now = 1;
                        squ = 1;
                        if (j > 1)  xs = lines[p][i][j - 1].x, ys = lines[p][i][j - 1].y;
                    }
                    if (now == 2)
                    {
                        if (map[xs][ys] == 1 ||(xs==-1 && ys==-1));
                        else
                        {
                            squ--;
                            pointp[now] += point[squ];
                            now = 1;squ = 1;
                            if (j > 1)  xs = lines[p][i][j - 1].x, ys = lines[p][i][j - 1].y;
                        }
                    }
                }
                if (map[x][y] == 2)
                {
                    if (now == map[x][y])  squ++;
                    if (now == 0)
                    {
                        now = 2;
                        squ = 1;
                        if (j > 1)  xs = lines[p][i][j - 1].x, ys = lines[p][i][j - 1].y;
                    }
                    if (now == 1)
                    {
                        if (map[xs][ys] == 2 || (xs == -1 && ys == -1));
                        else
                        {
                            squ--;
                            pointp[now] += point[squ];
                            now = 2;squ = 1;
                            if (j > 1)  xs = lines[p][i][j - 1].x, ys = lines[p][i][j - 1].y;
                        }
                    }
                }
            }
            if (now > 0 && map[xs][ys] != 3 - now)
            {
                squ--;
                pointp[now] += point[squ];
            }
        }
    }
    return pointp[1] - pointp[2];
}
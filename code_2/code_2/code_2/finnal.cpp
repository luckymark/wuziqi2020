
#include "finnal.h"
#include"board.h"
#include <iostream>
using namespace std;

#define MAXN 17
extern struct data
{
	int x, y;
}lines[9][MAXN * 3][MAXN * 3];
extern int NumLines[9][MAXN * 3];
extern int totLines[9];


int Won(int map[][MAXN])
{
	int now=-1,tot=0,x,y;
    for (int p = 0;p < 4;p++)
    {
        for (int i = 1;i <= totLines[p];i++)
        {
            now = 0, tot = 0;
            for (int j = 1;j <= NumLines[p][i];j++)
            {
                x = lines[p][i][j].x;
                y = lines[p][i][j].y;
                if (map[x][y] == now)
                {
                    tot++;
                }
                else
                {
                    now = map[x][y];
                    tot = 1;
                }
                if (tot == 5 && now>0)
                {
                    return now;
                }
            }
        }
    }
	return 0;
}

#include<graphics.h>
#include <cstdio>
#include<conio.h>
#include <iostream>
#include<cmath>


#include "board.h"
#include "DeepSearch.h"
#include "finnal.h"
#include "evalute.h"

using  namespace std;

int map[MAXN][MAXN];

int End()
{
    int flag = Won(map);
    if (flag)
    {
        if (flag == 1)
        {
            printf("You lost\n");
        }
        if (flag == 2)
        {
            printf("You Won\n");
        }
        _getch();
        closegraph();
        return 1;
    }
    return 0;
}

extern struct data
{
    int x, y;
}lines[9][MAXN * 3][MAXN * 3];
extern int NumLines[9][MAXN * 3];
extern int totLines[9];
int main()
{    
    initboard();
    Pushboard();
   int pointp = 0, alpha = -5555, beta = (1 << 30);
    while (1)
    {
        input_black(map);  //black chess(gamer) choose
        if (map[1][1]) pointp++;
        if (End())  break;


        alpha = -(1<<30), beta = (1 << 30);
        dfs(0,map , alpha, beta);   //white chess (AI) choose

        if (End())  break;
    }
    _getch();
    closegraph();
    return 0;
}





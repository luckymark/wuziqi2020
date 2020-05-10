//
// Created by dell on 2020/4/21.
//

#include<cstdio>
#include "Deepsearch.h"
#include "generator.h"
#include "evalute.h"
#include "board.h"

#define LAYTOP 4

struct gen_loca board[MAXN * MAXN];

int dfs(int map[][MAXN], int lay, int alpha, int beta)   //lay even AI Max  lay odd human Min
{
    if (lay == LAYTOP)
    {
        return calc_point(map);
    }

    int color;
    if (lay % 2 == 0)  color = 1;  //AI white choose
    else color = 2;       // human black choose

    int tot = 0;
    GetLocation(map, color, &tot,board);   //there are some problems that I will improve them next time


    int i = 0;
    int z;
    struct gen_loca Path;
    for (i = 0;i < tot;i++)
    {
        if (alpha >= beta)  break;
        map[board[i].x][board[i].y] = color;
        int x = board[i].x;
        int y = board[i].y;

        z = dfs(map, lay + 1, alpha, beta);

        map[x][y] = 0;
        if (lay % 2 == 0)     //Max
        {
            if (alpha < z)  alpha = z, Path = board[i];
        }
        else {       //Min
            if (beta > z)  beta = z, Path = board[i];
        }
    }

    if (lay == 0)
    {
        map[Path.x][Path.y] = 1;    //Choose
        Print_White(Path.x, Path.y);
    }

    if (lay % 2 == 0)  return alpha;
    else  return beta;
}
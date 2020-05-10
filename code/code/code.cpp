
#include<graphics.h>
#include <cstdio>
#include<conio.h>
#include <iostream>
#include<cmath>

#include "board.h"
#include "evalute.h"
#include "DeepSearch.h"
#include "define_var.h"
#include "finnal.h"

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
}
int main()
{
    initboard();
    int point = 0, alpha = -5555, beta = (1 << 30);
    int now = 0;
    while (1)
    {
        input_black(map);  //black chess(gamer) choose
        alpha = -5555, beta = (1 << 30);         
        if (End())  break;

        dfs(map, 0, alpha, beta);   //white chess (AI) choose
       
       // break;
        if (End())  break;
 
   
    }
    _getch();
    closegraph();   
    return 0;
}





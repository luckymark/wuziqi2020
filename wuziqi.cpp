//
// Created by pointkab on 2020/4/17.
//

#include "initWindow.h"
#include "game.h"
#include <cstdio>

using namespace std;

int main()
{

    InitWindow();
    //setfillcolor(BLACK);
    //circle(18,22,15);左上：18 23   右上： 455 23   DX = 31
    //                  左下：18 460  右下： 455 460  DY = 31    475
    //floodfill(18,22,BLACK);
    Game_Body();
    closegraph();//关闭绘图窗口
}

#include <graphics.h>
#include <conio.h>
#include <cstdio>
#include<cmath>

#include "board.h"


int dis(int x, int y, int x1, int y1)
{
    if (sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1)) <= 15)
    {
        return 1;
    }
    return 0;
}

void input_black(int map[][MAXN])
{
    MOUSEMSG m;
    int x, y;
    setfillcolor(RGB(28, 28, 28));
    while (1)
    {
        m = GetMouseMsg();


    /*    if(m.uMsg==WM_MOUSEMOVE)
            // 鼠标移动的时候画红色的小点
            putpixel(m.x, m.y, RED);*/
        if (m.uMsg == WM_LBUTTONDOWN)
        {
            x = m.x / 40;
            y = m.y / 40;
            //fillcircle(x * 40, y * 40, 15);
            if(map[x][y])  rectangle(m.x - 10, m.y - 10, m.x + 10, m.y + 10);
            if (x > 0 && y > 0 && dis(x * 40, y * 40, m.x, m.y) && map[x][y]==0)
            {
                fillcircle(x * 40, y * 40, 15);
                map[x][y] = 2;
                break;
            }
            if (x > 0 && y + 1 < 16 && dis(x * 40, (y + 1) * 40, m.x, m.y) && map[x][y+1]==0)
            {
                fillcircle(x * 40, (y + 1) * 40, 15);
                map[x][y + 1] = 2;
                break;
            }
            if (x + 1 < 16 && y > 0 && dis((x + 1) * 40, y * 40, m.x, m.y)&& map[x+1][y]==0)
            {
                fillcircle((x + 1) * 40, y * 40, 15);
                map[x + 1][y] = 2;
                break;
            }
            if (x + 1 < 16 && y + 1 < 16 && dis((x + 1) * 40, (y + 1) * 40, m.x, m.y) && map[x+1][y+1]==0)
            {
                fillcircle((x + 1) * 40, (y + 1) * 40, 15);
                map[x + 1][y + 1] = 2;
                break;
            }
        }
    }
}

void Print_White(int x, int y)
{
    setfillcolor(0xFFFFFF);
    fillcircle((x ) * 40, (y ) * 40, 15);
}
void initboard()
{
    initgraph(LENGHT, WEIGHT);
    setbkcolor(RGB(245, 255, 250));
    cleardevice();

    int i = 0;
    setlinecolor(0x000000);
    line(0, 0, LENGHT, 0);
    line(0, 0, 0, WEIGHT);
    for (i = 1;i <= LINE;i++)
    {
        line(0, WEIGHT / LINE * i, LENGHT, WEIGHT / LINE * i);
        line(LENGHT / LINE * i, 0, LENGHT / LINE * i, WEIGHT);
    }

}

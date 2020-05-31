#include <graphics.h>
#include <conio.h>
#include <cstdio>
#include<cmath>

#include "board.h"

 struct data
{
    int x, y;
}lines[9][MAXN * 3][MAXN * 3];
int NumLines[9][MAXN * 3];
int totLines[9];

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
    int x, y,x1,y1;
    setfillcolor(RGB(28, 28, 28));
    while (1)
    {
        m = GetMouseMsg();


        /*    if(m.uMsg==WM_MOUSEMOVE)
                // 鼠标移动的时候画红色的小点
                putpixel(m.x, m.y, RED);*/
        if (m.uMsg == WM_LBUTTONDOWN)
        {
            y = m.x / 40;
            x = m.y / 40;
            x1 = m.x / 40;
            y1 = m.y / 40;
            //fillcircle(x * 40, y * 40, 15);
            if (map[x][y])  rectangle(m.x - 10, m.y - 10, m.x + 10, m.y + 10);
            if (x1 > 0 && y1 > 0 && dis(x1 * 40, y1 * 40, m.x, m.y) && map[x][y] == 0)
            {
                fillcircle(x1 * 40, y1 * 40, 15);
                map[x][y] = 2;
                break;
            }
            if (x1 > 0 && y1 + 1 < 16 && dis(x1 * 40, (y1 + 1) * 40, m.x, m.y) && map[x+1][y] == 0)
            {
                fillcircle(x1 * 40, (y1 + 1) * 40, 15);
                map[x+1][y] = 2;
                break;
            }
            if (x1 + 1 < 16 && y1 > 0 && dis((x1 + 1) * 40, y1 * 40, m.x, m.y) && map[x ][y+ 1] == 0)
            {
                fillcircle((x1 + 1) * 40, y1 * 40, 15);
                map[x][y+1] = 2;
                break;
            }
            if (x1 + 1 < 16 && y1 + 1 < 16 && dis((x1 + 1) * 40, (y1 + 1) * 40, m.x, m.y) && map[x + 1][y + 1] == 0)
            {
                fillcircle((x1 + 1) * 40, (y1 + 1) * 40, 15);
                map[x + 1][y + 1] = 2;
                break;
            }
        }
    }
}

void Print_White(int x, int y)
{
    setfillcolor(0xFFFFFF);
    fillcircle((y) * 40, (x) * 40, 15);
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

void Pushboard()
{
    for (int i = 1;i <= MAXN - 2;i++)
    {
        totLines[0]++;
        for (int j = 1;j <= MAXN - 2;j++)
        {
            lines[0][totLines[0]][++NumLines[0][totLines[0]]].x = i;
            lines[0][totLines[0]][NumLines[0][totLines[0]]].y = j;
        }
    }
    for (int j = 1;j <= MAXN - 2;j++)
    {
        totLines[1]++;
        for (int i = 1;i <= MAXN - 2;i++)
        {
            lines[1][totLines[1]][++NumLines[1][totLines[1]]].x = i;
            lines[1][totLines[1]][NumLines[1][totLines[1]]].y = j;
        }
    }

   int sx = 1, sy = 1,i,j;
    while (sx <= MAXN - 2 && sy <= MAXN - 2)
    {
        totLines[2]++;
        i = sx, j = sy;
        while (i >= 1 && j < MAXN - 1 && i < MAXN && j >= 1)
        {
            lines[2][totLines[2]][++NumLines[2][totLines[2]]].x = i;
            lines[2][totLines[2]][NumLines[2][totLines[2]]].y = j;
            i = i - 1;j = j + 1;
        }
        if (sx == MAXN - 2)
        {
            sy++;
        }
        else
        {
            sx++;
        }
    }
   sx = 1, sy = MAXN - 2;
    while (sx <= MAXN - 2 && sy>=1 )
    {
        totLines[3]++;
        i = sx, j = sy;
        while (i >= 1 && j < MAXN - 1 && i < MAXN && j >= 1)
        {
            lines[3][totLines[3]][++NumLines[3][totLines[3]]].x = i;
            lines[3][totLines[3]][NumLines[3][totLines[3]]].y = j;
            i = i + 1;j = j + 1;
        }
        if (sy == 1)
        {
            sx++;
        }
        else
        {
            sy--;
        }
    }
}
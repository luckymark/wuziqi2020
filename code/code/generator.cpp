

#include "generator.h"
#include "evalute.h"
#include<cstdio>

struct gen_loca AuXi[MAXN * MAXN];

int Max(int x, int y)
{
    return x > y ? x : y;
}
int Min(int x, int y)
{
    return x < y ? x : y;
}


/*void SortPoint(int start, int end, struct gen_loca location[])
{
    if (start >= end)  return;
    int mid = (start + end) / 2;
    SortPoint(start, mid, location);
    SortPoint(mid + 1, end, location);

    int now1 = start, now2 = mid + 1, now3 = start;
    while (now1 <= mid && now2 <= end)
    {
        if (location[now1].point > location[now2].point) AuXi[now3] = location[now1], now1++;
        else  AuXi[now3] = location[now2], now2++;
        now3++;
    }
    while (now1 <= mid)
    {
        AuXi[now3] = location[now1], now1++;
        now3++;
    }
    while (now2 <= mid)
    {
        AuXi[now3] = location[now2], now2++;
        now3++;
    }
    int i;
    for (i = start;i <= end;i++)
    {
        location[i] = AuXi[i];
    }

}*/


int FindValid(int x, int y, int map[][MAXN])
{
    int x1 = Max(x - 2, 1);
    int x2 = Min(x + 2, MAXN - 2);
    int y1 = Max(y - 2, 1);
    int y2 = Min(y + 2, MAXN - 2);
    int i, j;

    for (i = x1;i <= x2;i++)
    {
        for (j = y1;j <= y2;j++)
        {
            if (map[i][j]>0) return 1;
        }
    }
    return 0;
}


void GetLocation(int map[][MAXN], int color, int* total,gen_loca board[MAXN*MAXN])
{
    int i, j, tot = 0;
    for (i = 1;i < MAXN-1;i++)
    {
        for (j = 1;j < MAXN-1;j++)
        {
            if (!map[i][j])
            {
                if (FindValid(i, j, map))
                {
                    board[tot].x = i;board[tot].y = j;
                    map[i][j] = color;
                   // location[tot].point = calc_part_point(map, color, i, j);

                    map[i][j] = 0;
                    tot++;
                }
            }
        }
    }
    // SortPoint(0,tot-1,location);
    *total = tot;

}

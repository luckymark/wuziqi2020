
#include "evalute.h"

// we use white chess to evalute the point
//a '1' represents a white chess

int Mx[8][2] = { {1,0},{-1,0},     //up  down
              {0,1},{0,-1},     // left right
              {1,1},{-1,-1},
              {1,-1},{-1,1}
};
int score[6] = { 0,0,100,1000,10000,100000 };

int white_black(int white, int black)
{
    if (black >= 2)  return 0;
    white -= black;
    return score[white];
}

int lines_point(int map[][MAXN])
{
    int point = 0;
    int i, j;
    int white, black;
    for (i = 1;i < MAXN-1;i++)
    {
        white = 0, black = 1;
        for (j = 1;j < MAXN-1;j++)
        {
            if (map[i][j] == 0) // empty
            {
                if (white != 0)   point += white_black(white, black);
                white = 0;black = 0;

            }
            else {
                if (map[i][j] == 1)  white++;
                else
                {
                    if (white != 0)
                    {
                        black++;
                        point += white_black(white, black);
                        white = 0;black = 1;
                    }
                    else
                    {
                        black = 1;
                    }

                }

            }
        }
        if (white != 0)
        {
            black++;
            point += white_black(white, black);
        }
    }
    return point;
}

int rank_point(int map[][MAXN])
{
    int point = 0;
    int i, j;
    int white, black;
    for (j = 1;j < MAXN-1;j++)
    {
        white = 0, black = 1;
        for (i = 1;i < MAXN-1;i++)
        {
            if (map[i][j] == 0) // empty
            {
                if (white != 0)   point += white_black(white, black);
                white = 0;black = 0;

            }
            else {
                if (map[i][j] == 1)  white++;
                else
                {
                    if (white != 0)
                    {
                        black++;
                        point += white_black(white, black);
                        white = 0;black = 1;
                    }
                    else
                    {
                        black = 1;
                    }

                }

            }
        }
        if (white != 0)
        {
            black++;
            point += white_black(white, black);
        }
    }
    return point;
}
int left_point(int map[][MAXN])
{
    int point = 0;
    int i, j, sx, sy;
    int white, black;
    sx = 1, sy = 1;
    while (sx < MAXN-1 && sy < MAXN-1)
    {
        white = 0, black = 1;
        i = sx, j = sy;
        while (i >= 1 && j < MAXN-1 && i < MAXN && j >= 1)
        {
            if (map[i][j] == 0) // empty
            {
                if (white != 0)   point += white_black(white, black);
                white = 0;black = 0;

            }
            else {
                if (map[i][j] == 1)  white++;
                else
                {
                    if (white != 0)
                    {
                        black++;
                        point += white_black(white, black);
                        white = 0;black = 1;
                    }
                    else
                    {
                        black = 1;
                    }

                }

            }
            i = i - 1;j = j + 1;
        }
        if (white != 0)
        {
            black++;
            point += white_black(white, black);
        }
        if (sx == MAXN - 2)
        {
            sy++;
        }
        else {
            sx++;
        }
    }
    return point;
}

int right_point(int map[][MAXN])
{
    int point = 0;
    int i, j, sx, sy;
    int white, black;
    sx = 1, sy = MAXN - 2;
    while (sx < MAXN && sy >= 0)
    {
        white = 0, black = 1;
        i = sx, j = sy;
        while (i >= 1 && j < MAXN-1 && i < MAXN-1 && j >= 1)
        {
            if (map[i][j] == 0) // empty
            {
                if (white != 0)   point += white_black(white, black);
                white = 0;black = 0;

            }
            else {
                if (map[i][j] == 1)  white++;
                else
                {
                    if (white != 0)
                    {
                        black++;
                        point += white_black(white, black);
                        white = 0;black = 1;
                    }
                    else
                    {
                        black = 1;
                    }

                }

            }
            i = i - 1;j = j - 1;
        }
        if (white != 0)
        {
            black++;
            point += white_black(white, black);
        }
        if (sx == MAXN - 2)
        {
            sy--;
        }
        else {
            sx++;
        }
    }
    return point;
}

int calc_point(int map[][MAXN])
{
    int point = 0;
    point += lines_point(map) + rank_point(map) + left_point(map) + right_point(map);
    return point;
}

int legal(int x, int y)
{
    if (x < 0 || x >= MAXN)  return 0;
    if (y < 0 || y >= MAXN)  return 0;
    return 1;
}
int five(int map[][MAXN], int color, int x, int y)   //the chess not dead
{
    int now = 1, num = -5, flag = 0;
    int x1, y1;
    for (int i = 0;i < 8;i += 2)
    {
        flag = 0;
        x1 = x + Mx[i][0];y1 = y + Mx[i][1];
        while (1)
        {
            if (!legal(x1, y1))
            {
                flag = 1;break;
            }
            if (map[x1][y1] == color)
            {
                now++;
            }
            else
            {
                if (map[x1][y1] != 0)  flag = 1;
                break;
            }
            x1 = x1 + Mx[i][0];
            y1 = y1 + Mx[i][1];
        }

        x1 = x + Mx[i + 1][0];y1 = y + Mx[i + 1][1];
        while (1)
        {
            if (!legal(x1, y1))
            {
                flag = 1;break;
            }
            if (map[x1][y1] == color)
            {
                now++;
            }
            else
            {
                if (map[x1][y1] != 0)  flag = 1;
                break;
            }
            x1 = x1 + Mx[i + 1][0];
            y1 = y1 + Mx[i + 1][1];
        }


        if (now == 5)  return 5;
        else
        {
            if (flag) now = 0;
            if (now > num)  num = now;
        }
    }
    return num;
}
int calc_part_point(int map[][MAXN], int color, int x, int y)
{
    int z = five(map, color, x, y);
   // if (z == )
    return 1;
}
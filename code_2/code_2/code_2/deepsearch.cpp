#include "deepsearch.h"
#include "evalute.h"
#include "location.h"
#include "board.h"
#include "finnal.h"

extern struct loca
{
    int x, y, point;
}Loca[400];
extern int totLoca;
 int Min(int x, int y)
 {
     return x < y ? x : y;
 }
 int Max(int x, int y)
 {
     return x > y ? x : y;
 }
 int End1(int map[][MAXN])
 {
     int flag = Won(map);
     if (flag)
     {
         return 1;
     }
     return 0;
 }
 int dfs(int layer,int map[][MAXN], int alpha, int beta)
 {
     if (End1(map))  return calc_point(map);
     if (layer == 4)
     {
         int p = calc_point(map);
         return p;
     }
     int x, y,color; 
     if (!(layer & 1))  color = 1;
     else  color = 2;

     Getlocation(map,color);
     int nowX[400], nowY[400], totnow=totLoca;
      
     int PathX = 0, PathY = 0;


     for (int i = 1;i <= totnow;i++)  nowX[i] = Loca[i].x, nowY[i] = Loca[i].y;

     if (color == 2)
     {
        for (int i = 1;i <= totnow;i++)
        {
             x = nowX[i];y = nowY[i];
             map[x][y] = color;
             beta = Min(beta, dfs(layer + 1, map, alpha, beta));
             map[x][y] = 0;
             if (alpha >= beta)  return alpha;
         }
        return beta;
     }
     else
     {
         for (int i = 1;i <= totnow;i++)
         {
             x = nowX[i];y = nowY[i];
             map[x][y] = color;
             int p = dfs(layer + 1, map, alpha, beta);
             if (p > alpha)
             {
                  PathX = x;PathY = y;
                  alpha = p;
              }
             map[x][y] = 0;
             if (alpha >= beta)   return beta;
         }
         if (layer == 0)
         {
             Print_White(PathX, PathY);
             map[PathX][PathY] = 1;
         }
         return alpha;
     }
   
 }
#include "deepsearch.h"
#include "evalute.h"
#include "location.h"
#include "board.h"

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
 int dfs(int layer,int map[][MAXN], int alpha, int beta)
 {
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
             if (alpha >= beta)  return beta;
         }
        return beta;
     }
     else
     {
         for (int i = 1;i <= totnow;i++)
         {
             x = nowX[i];y = nowY[i];
             map[x][y] = color;
             if (layer == 0)
             {
                 int p = dfs(layer + 1, map, alpha, beta);
                 if (p > alpha)
                 {
                     PathX = x;PathY = y;
                     alpha = p;
                 }
             }
             else
                alpha = Max(alpha, dfs(layer + 1, map, alpha, beta));
             map[x][y] = 0;
             if (alpha >= beta)
             {
                 if (layer == 0)
                 {
                     Print_White(PathX, PathY);
                     map[PathX][PathY] = 1;
                 }
                 return alpha;
             }
         }
         if (layer == 0)
         {
             Print_White(PathX, PathY);
             map[PathX][PathY] = 1;
         }
         return alpha;
     }
   
 }
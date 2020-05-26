//
// Created by 20694 on 2020/5/12.
//

#ifndef GOBANG_PAWN_SCORE_H
#define GOBANG_PAWN_SCORE_H

#define w5 10000
#define a4 1000
#define d4 550
#define a3 500
#define d3 250
#define a2 200
#define d2 100


#include "Main.h"
int win5(const int*left,const int*right,int length,int color);
int alive4(const int*left,const int*right,int length,int color);
int alive3(const int *left,const int *right,int length,int color);
int alive2(const int *left,const int *right,int length,int color);
int dead4(const int *left,const int *right,int length,int color);
int dead3(const int *left,const int *right,int length,int color);
int dead2(const int *left,const int *right,int length,int color);

#endif //GOBANG_PAWN_SCORE_H

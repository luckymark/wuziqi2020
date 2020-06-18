//
// Created by 20694 on 2020/5/12.
//

#ifndef GOBANG_PAWN_SCORE_H
#define GOBANG_PAWN_SCORE_H

const int w5=10000;
const int a4=1000;
const int d4=550;
const int a3=500;
const int d3=250;
const int a2=200;
const int d2=100;


#include "main.h"
int win5(const int*left,const int*right,int length,int color);
int alive4(const int*left,const int*right,int length,int color);
int alive3(const int *left,const int *right,int length,int color);
int alive2(const int *left,const int *right,int length,int color);
int dead4(const int *left,const int *right,int length,int color);
int dead3(const int *left,const int *right,int length,int color);
int dead2(const int *left,const int *right,int length,int color);

#endif //GOBANG_PAWN_SCORE_H

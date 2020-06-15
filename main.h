//
// Created by 20694 on 2020/5/10.
//
#ifndef GOBANG_MAIN_H
#define GOBANG_MAIN_H

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>

using std::cin;
using std::cout;
using std::string;

#define black 1
#define white 2
#define empty 0
#define row 16
#define col 16
#define square 225
#define Number_of_layers 2

typedef struct POINT{
    int x;
    int y;
    int score;
}point;
void initialization(point*p0);
int state_score(int x,int y,int color);
int get_color_(int color);
int exam();
int max_min(int deep,int color);
#endif //GOBANG_MAIN_H

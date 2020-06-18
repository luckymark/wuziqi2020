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
#define Number_of_layers 4

enum {yes,no};
enum {red,blue};

typedef struct Point{
    int x;
    int y;
    int score;
}point;
void initialization(point*p0);
int state_score(int x,int y,int color);
int get_color_(int color);
int max_min(int deep,int color);
int is_end(int x,int y,int color);
void print();
void ShadowWindowLine(const char* s,int left,int top,int right,int bottom,int shadow,int color);
#endif //GOBANG_MAIN_H

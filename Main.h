//
// Created by 20694 on 2020/5/10.
//
#ifndef GOBANG_MAIN_H
#define GOBANG_MAIN_H

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>

using std::cin;
using std::cout;
using std::string;

#define black 1
#define white 2
#define empty 0
#define row 16
#define col 16
#define Number_of_layers 2

int state_score(int x,int y,int color);
int get_color_(int color);
#endif //GOBANG_MAIN_H

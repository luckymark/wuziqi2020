//
// Created by 20694 on 2020/6/17.
//

#ifndef GOBANG_PRINT_H
#define GOBANG_PRINT_H

#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <string>
#include <cstring>
using std::string;

enum {yes,no};
enum {red,blue};

void ShadowWindowLine(const char* s,int left,int top,int right,int bottom,int shadow,int color);
int is_end(int x,int y,int color);
void MouseEvent();
#endif //GOBANG_PRINT_H

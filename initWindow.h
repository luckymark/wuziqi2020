//
// Created by pointkab on 2020/4/23.
//

#ifndef WUZIQI2020_INITWINDOW_H
#define WUZIQI2020_INITWINDOW_H

#include <cstdio>
#include <graphics.h>
#define START_X 19
#define START_Y 23
#define DXY 31
#define RIGHT_BODER 475
#define QIPAN_SIZE 15
#define TOLERANCE 6

void InitWindow();//初始化游戏界面

int PutItems(const int x, const int y, const int Is_B_OR_W, const int Ai_Or_Player);

int Accurate_Coord(const int coord_value, const int coord_type);

int Judge(int temp, int Accurate_coord);

int Judge_Is_Empty(const int x, const int y);//判断落子是否为空位

#endif //WUZIQI2020_INITWINDOW_H

//
// Created by hw730 on 2020/4/9.
//

#ifndef CHESSFINAL_CHESSGLOBALCONST_H
#define CHESSFINAL_CHESSGLOBALCONST_H
#include <QWidget>
#include <QApplication>
#include <iostream>
#include<QPainter>
#include<QMouseEvent>
#include<QPushButton>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ll long long

#define PAINT_X 200
#define PAINT_Y 100
#define SHOW_CHESS_LENGTH 700
#define SHOW_CHESS_HEIGHT 700
#define DISTANCE 50
#define CHESS_LENGTH (17)
#define CHESS_HEIGHT (17)
#define RES 15
#define ROUND 10

#define MAX_CHOICE 10
#define depth_MAX 4
#define STEPS 3
//文本框大小按照打印的XY坐标而定（与正常的反过来了)
#define TOP_X 1050
#define TOP_Y 500
#define BOTTOM_X 1150
#define BOTTOM_Y 600

#define BUTTON_W 100
#define BUTTON_H 100

#define C_NONE 0
#define C_BLACK 1
#define C_WHITE 2
#define C_BOUND 3
#define WIN 1000000000
#define LOSE -80000000000
#define WHITE_LIVE_4 50000000
#define BLACK_LIVE_4 -300000000

#define WHITE_LIVE_3 400
#define BLACK_LIVE_3 -8000

#define WHITE_LIVE_2 20
#define BLACK_LIVE_2 -40

#define WHITE_LIVE_1 1
#define BLACK_LIVE_1 -2

//SLEEP
#define WHITE_SLEEP_4 400
#define BLACK_SLEEP_4 -8000

#define WHITE_SLEEP_3 20
#define BLACK_SLEEP_3 -40

#define WHITE_SLEEP_2 1
#define BLACK_SLEEP_2 -2



#endif //CHESSFINAL_CHESSGLOBALCONST_H

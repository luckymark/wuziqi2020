#ifndef DEF_H
#define DEF_H

#define NUMBER 15
#define MAX_LEVEL 8

#define C_EMPTY 0
#define C_WHITE 1
#define C_BLACK 2
//C - Color

#define S_WAIT 0
#define S_TIE 1
#define S_WIN 2
#define S_LOSE 3
//S - Status

//白棋
#define M_WIN 10000000
#define M_FLEX4 100000
#define M_BLOCK4 1000
#define M_FLEX3 1000
#define M_BLOCK3 100
#define M_FLEX2 100
#define M_BLOCK2 10
#define M_FLEX1 10

//黑棋
#define M_lose 50000000
#define M_flex4 5000000
#define M_block4 50000
#define M_flex3 5000
#define M_block3 500
#define M_flex2 500
#define M_block2 50
#define M_flex1 50

extern int weight[5][2][2];
//第一维是分值等级
//第二维是活0还是眠1类型
//第三维是白0还是黑1

#endif // DEF_H

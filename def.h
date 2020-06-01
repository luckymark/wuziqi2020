#ifndef DEF_H
#define DEF_H

//为什么可以使用一个头文件来包含全部宏定义呢？
//因为，include指令会在define指令之前执行

#define NUMBER 15   //棋盘大小
#define MAX_LEVEL 8 //最大搜索层数

#define C_EMPTY 0
#define C_WHITE 1
#define C_BLACK 2
//C - Color 棋子颜色宏定义

#define S_WAIT 0
#define S_TIE 1
#define S_WIN 2
#define S_LOSE 3
//S - Status    棋局状态宏定义

//白棋棋形打分
#define M_WIN 10000000  //连5
#define M_FLEX4 100000  //活4
#define M_BLOCK4 1000   //冲4
#define M_FLEX3 1000    //活3
#define M_BLOCK3 100    //眠3
#define M_FLEX2 100     //活2
#define M_BLOCK2 10     //眠2
#define M_FLEX1 10      //活1

//这里并没有多少数学依据hhh

//黑棋棋形打分
#define M_lose 50000000 //连5
#define M_flex4 5000000 //活4
#define M_block4 50000  //冲4
#define M_flex3 5000    //活3
#define M_block3 500    //眠3
#define M_flex2 500     //活2
#define M_block2 50     //眠2
#define M_flex1 50      //活1

extern int weight[5][2][2];
//第一维是分值等级
//第二维是活（0）还是眠(1)类型
//第三维是白(0)还是黑(1)

#endif // DEF_H

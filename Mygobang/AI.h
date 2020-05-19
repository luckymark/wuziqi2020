//
// Created by 彭琳峰 on 2020/4/21.
//

#pragma once
#include<QPoint>
#include <cstring>
//棋型代号 下标 权重
#define OTHER 0          //0,其他棋型不考虑
#define WIN 1           //100000,白赢
#define LOSE 2           //-10000000
#define FLEX4 3             //50000,白活4
#define flex4 4             //-80000
#define BLOCK4 5                //400
#define block4 6                //-80000
#define FLEX3 7             //400
#define flex3 8         //-8000
#define BLOCK3 9            //20
#define block3 10           //-40
#define FLEX2 11            //20
#define flex2 12            //-40
#define BLOCK2 13           //1
#define block2 14           //-2
#define FLEX1 15            //1
#define flex1 16            //-2

//棋型辨识数组,0无子,1黑子,2白子,3边界
enum TypeOnBoard {		//枚举类型，
    Nobody = 0,Black =1,White = 2,Margin=3
};

struct Point{
    int x;
    int y;
};
struct RESULT{
    int socre;
    int winner;
    int STAT[8];
};
struct DECISON{
    QPoint pos;
    int socre;
};
struct POINTS{
    QPoint pos[10];
    int socre[10];
};
class AI {
private:
    int tuple6type[4][4][4][4][4][4];

public:
    void CopyBoard(int copyboard[15][15],const int chessboard[15][15]);
    int abSearch(const int chessBoard[15][15],int depth,int alpha,int beta);
    POINTS SeekPoints(const int chessboard[15][15]);
    RESULT evaluate(const int chessboard[15][15]);
    int scoreTable[17][17];
    AI();
    DECISON decison;
private:


    void reverseBoard(int pInt[15][15],const int chessboard[15][15]);
    void printToLog(const char string[]);
};
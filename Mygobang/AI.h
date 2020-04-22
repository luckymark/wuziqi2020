//
// Created by 彭琳峰 on 2020/4/21.
//

#pragma once
#include<QPoint>
static const int ONE = 10;
static const int TWO = 100;
static const int THREE = 1000;
static const int FOUR = 100000;
static const int FIVE = 1000000;
static const int BLOCKED_ONE = 1;
static const int BLOCKED_TWO = 10;
static const int BLOCKED_THREE = 100;
static const int BLOCKED_FOUR = 10000;

//贪心计分
static const int TypePolluted = 0;
static const int BLANK = 7;
static const int TypeB = 35;
static const int TypeBB = 800;
static const int TypeBBB = 15000;
static const int TypeBBBB = 800000;

static const int TypeW = 15;
static const int TypeWW = 400;
static const int TypeWWW = 1800;
static const int TypeWWWW = 100000;

struct Point{
    int x;
    int y;
};
class AI {
public:
    Point point;
    void calculateScore(const int chessBoard[15][15]);
    Point findBestScore(const int score[15][15]);
    int judgeTypeAndGiveScore(const int cntWhite,const int cntBlack);
    int scoreTable[15][15];
    AI();
private:



};
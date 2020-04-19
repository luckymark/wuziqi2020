//
// Created by hw730 on 2020/4/19.
//

#ifndef CHESSAIUPD_CHESSSTRUCT_H
#define CHESSAIUPD_CHESSSTRUCT_H
#include"chesslib.h"
#include"chessglobalconst.h"
struct boardStatus{
    ll status,score;
};
struct Points{
    int x,y;
};

struct decision{
    Points pos[MAX_CHOICE];
    ll score[MAX_CHOICE];
};
#endif //CHESSAIUPD_CHESSSTRUCT_H

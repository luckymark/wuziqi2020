//
// Created by pointkab on 2020/4/24.
//

#ifndef WUZIQI2020_GAME_H
#define WUZIQI2020_GAME_H

#include "initWindow.h"
#define AI_CHESS -1
#define PLAYER_CHESS 1
#define NONE 0

struct currentchess{
    COORD coord;
    int type;
};

extern int ChessNums;

extern struct currentchess CurrentChess[225];

extern int Qipan_Array[QIPAN_SIZE][QIPAN_SIZE];

int Game_Body();//游戏主体

int Player_Play();//玩家下棋

void AI_Play();//电脑下棋

int IsValueChess(int i, int j);

int EvaluateAllChess();

int minMax(int i, int j, int depth);

void VirtualPut(int i, int j, int depth);

void DeleChess(int i, int j);


#endif //WUZIQI2020_GAME_H

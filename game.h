//
// Created by pointkab on 2020/4/24.
//

#ifndef WUZIQI2020_GAME_H
#define WUZIQI2020_GAME_H

#include "initWindow.h"
#define AI_CHESS -1
#define PLAYER_CHESS 1
#define NONE 0
#define DEPTH 4

struct currentchess{
    COORD coord;
    int type;
};

struct ChessScore{
    int chesstype;//1代表玩家，-1代表电脑
    COORD coord;
    int score;
};

extern struct ChessScore Delocation;

extern int ChessNums;

extern struct currentchess CurrentChess[225];

extern int Qipan_Array[QIPAN_SIZE][QIPAN_SIZE];

int Game_Body();//游戏主体

int Player_Play();//玩家下棋

void AI_Play();//电脑下棋

int Search_Tree(int depth, int alpha, int beta);

int GetValueChess(ChessScore*scores, int depth, int alpha, int beta);

int EvaluateAllChess(int judge);

void VirtualPut(ChessScore * scores, int i);

void DeleChess(ChessScore * scores, int k);

void Sort(ChessScore* scores, int count, int depth);

int Matchline(int y, int x, int matchChess[15][15][4],int judge);

int Restart();

void JudgeWin(int result);

#endif //WUZIQI2020_GAME_H

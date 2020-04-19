//
// Created by hw730 on 2020/4/19.
//

#ifndef CHESSAIUPD_CHESSGLOBALVARIABLE_H
#define CHESSAIUPD_CHESSGLOBALVARIABLE_H
#include"chessglobalconst.h"
#include"chessstruct.h"
extern Points AIStep;
extern int R,R1;
extern int dir[8][2];
extern int board[CHESS_HEIGHT][CHESS_LENGTH];
extern QPoint q[CHESS_HEIGHT * CHESS_LENGTH];
extern QPoint q1[CHESS_HEIGHT * CHESS_LENGTH];
extern int col[CHESS_HEIGHT * CHESS_LENGTH];
extern ll chess_6_type[4][4][4][4][4][4];
extern ll zob[CHESS_HEIGHT][CHESS_LENGTH][2];
extern std::map<ll,boardStatus > mp;
extern ll Hash;
extern std::map<ll,ll> vis;
#endif //CHESSAIUPD_CHESSGLOBALVARIABLE_H

//
// Created by hw730 on 2020/4/19.
//

#include "chessglobalvariable.h"

ll chess_6_type[4][4][4][4][4][4];
int dir[8][2] = {{0,1},{1,0},{1,1},{1,-1},{-1,0},{0,-1},
                 {-1,1},{-1,-1}};
int board[CHESS_HEIGHT][CHESS_LENGTH];
int R = 0,R1 = 0;
QPoint q[CHESS_HEIGHT * CHESS_LENGTH];
QPoint q1[CHESS_HEIGHT * CHESS_LENGTH];
int col[CHESS_HEIGHT * CHESS_LENGTH];
Points AIStep;
ll zob[CHESS_HEIGHT][CHESS_LENGTH][2];
std::map<ll,boardStatus > mp;
std::map<ll,ll> vis;
ll Hash = 0;
//
// Created by hw730 on 2020/4/19.
//

#ifndef CHESSAIUPD_ALPHABETA_H
#define CHESSAIUPD_ALPHABETA_H

#include"chessglobalconst.h"
#include"chesslib.h"
#include"chessglobalvariable.h"
#include"chessstruct.h"
#include <QtWidgets/QWidget>

void AI(int (&board)[CHESS_HEIGHT][CHESS_LENGTH]);
ll alphaBetaSearch(int (&board)[CHESS_HEIGHT][CHESS_LENGTH], int depth, ll alpha, ll beta,ll zobrist);
decision findPoints(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],ll zobrist);
bool judgePoints(int x,int y);
boardStatus evaluateBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],ll zobrist);
void copychess(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&sameBoard)[CHESS_HEIGHT][CHESS_LENGTH]);
void revBoard(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],int (&reverseBoard)[CHESS_HEIGHT][CHESS_LENGTH]);
bool judgeChessBoardStatus(int (&board)[CHESS_HEIGHT][CHESS_LENGTH],ll zobrist);
void init_zobrist();
ll Rand();


#endif //CHESSAIUPD_ALPHABETA_H

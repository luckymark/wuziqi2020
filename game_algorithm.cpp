//
// Created by pointkab on 2020/4/28.
//
#include "game.h"

typedef struct ChessScore{
    int chesstype;//-1代表玩家，1代表电脑
    COORD coord;
    int score;
}chessScore;

chessScore score[225];

int steps = -1;

int Search_Tree(int alpha,int beta, int depth){
    int i, j;
    for (i = 0; i < QIPAN_SIZE; i++)
    {
        for (j = 0; j < QIPAN_SIZE; j++)
            {
                if (IsValueChess(i, j)){
                    VirtualPut(i, j, depth);//预测下棋
                    if (depth == 1){
                        score[steps].score = EvaluateAllChess();
                        DeleChess(i, j);
                        break;
                    }
//                    if (depth%2 == 0)//电脑层
//                    {
//                        alpha = minMax(i, j, depth);
//                    } else{
//                        beta = minMax(i, j, depth);
//                    }//玩家层
                      score[steps].score =  Search_Tree(alpha, beta, depth-1);
                      DeleChess(i, j);
                    }
            }
    }
    return minMax(i, j, depth);
}

int IsValueChess(int i, int j){
    int m, n;
    int Value_Width = 2;//有效宽度
    int longx = 5;
    int longy = 5;
    int beginX, beginY;
    if (Qipan_Array[i][j] != 0)
    {
        return 0;
    }//有子
    else{
        if ((i - Value_Width) < 0)
            {beginX = 0;}
        else
            {beginX = i-Value_Width;}
        if((j - Value_Width) < 0)
            {beginY = 0;}
        else
            {beginY = j - Value_Width;}
        if (beginX == 0)
        {longx = 3;}
        for (m = beginX; m< beginX + longx; m++)
        {
            if ((beginX + 4) > 15)
            { break;}
            if (beginY == 0)
            {longy = 3;}
            for (n = beginY; n < beginY + longy; n++)
            {
                if ((beginY + 4) > 15)
                { break;}
                if (Qipan_Array[m][n] != 0)
                { return 1;}
            }
        }
        return 0;
    }
}

int EvaluateAllChess(){
    return 0;
}

int minMax(int i, int j, int depth){
    int result;
    return result;
}

void VirtualPut(int i, int j, int depth){
    steps++;
    int chesstype;
    if (depth%2 == 0)//电脑层
    {
        chesstype = -1;
    } else {//玩家层
        chesstype = 1;
    }
    score[steps].chesstype = chesstype;
    score[steps].coord.X = i;
    score[steps].coord.Y = j;
    Qipan_Array[i][j] = chesstype;
}

void DeleChess(int i, int j){
    Qipan_Array[i][j] = 0;
}
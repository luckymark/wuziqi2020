//
// Created by 彭琳峰 on 2020/4/23.
//
#include <cstdio>
#include <iostream>
#include <cstring>
//贪心计分
static const int TypePolluted = 0;
static const int BLANK = 7;
static const int TypeB = 35;
static const int TypeBB = 800;
static const int TypeBBB = 15000;
static const int TypeBBBB = 800000;

static const int TypeW = 15;
static const int TypeWW = 400;
static const int TypeWWW = 18000;
static const int TypeWWWW = 1000000;
enum Turns {		//枚举类型，默认人是白棋，白棋在棋盘上设为1，黑棋为-1
    White = 1, Black = -1,Nobody = 0
};
int BoardLength = 15;
int chessBoard[15][15]={0};
int judgeTypeAndGiveScore( int cntWhite, int cntBlack) {

    int scoreBlack = 0;
    int scoreWhite = 0;
    if(cntBlack!=0&&cntWhite!=0)
    {
        scoreBlack += TypePolluted;
        scoreWhite += TypePolluted;
    } else{
        if (cntWhite==0&&cntBlack==0) scoreBlack += BLANK;

        if (cntWhite==0&&cntBlack==1) scoreBlack += TypeB;
        if (cntWhite==0&&cntBlack==2) scoreBlack += TypeBB;
        if (cntWhite==0&&cntBlack==3) scoreBlack += TypeBBB;
        if (cntWhite==0&&cntBlack==4) scoreBlack += TypeBBBB;

        if (cntWhite==1&&cntBlack==0) scoreBlack += TypeW;
        if (cntWhite==2&&cntBlack==0) scoreBlack += TypeWW;
        if (cntWhite==3&&cntBlack==0) scoreBlack += TypeWWW;
        if (cntWhite==4&&cntBlack==0) scoreBlack += TypeWWWW;
    }
    return scoreBlack+scoreWhite;
}
int main() {


    int cntWhite, cntBlack;
    for (int i = 0; i <=15 ; ++i) {
        for (int j = 0; j <=15 ; ++j) {
            chessBoard[i][j]=0;
        }
    }
    for (int i = 0; i <=15; ++i) {
        for (int j = 0; j <=15 ; ++j) {
       int pointscore=0;
       //hengxiangsou
            for (int k = j - 4; k <= j; ++k) { //枚举左端点
                if (k < 0) {
                    continue;
                } else if (k + 4 > BoardLength) { break; }
            //搜一个小条
                cntWhite = 0, cntBlack = 0;
                for (int l = k; l <= k + 4; ++l) {
                    if (chessBoard[i][l] == White) cntWhite++;
                    else if (chessBoard[i][l] == Black) cntBlack++;
                }
        //给这个小条打分
                pointscore += judgeTypeAndGiveScore(cntWhite, cntBlack);

            }
         //   printf("%7d\n",pointscore);
        //纵向搜
            for (int k = i - 4; k <= i; ++k) {  //枚举上端点
                if (k < 0) {
                    continue;
                } else if (k + 4 > BoardLength) { break; }
//搜一个小条
                cntWhite = 0, cntBlack = 0;
                for (int l = k; l <= k + 4; ++l) {
                    if (chessBoard[l][j] == 1) cntWhite++;
                    else if (chessBoard[l][j] == -1) cntBlack++;
                }
//给这个小条打分
                pointscore += judgeTypeAndGiveScore(cntWhite, cntBlack);

            }
         //   printf("%7d\n",pointscore);
        //主对角线搜
            for (int p = i - 4, k = j - 4; k <= j; ++k, ++p) { //枚举左上端点
                if (k < 0 || p < 0) continue;
                else if (k + 4 > BoardLength || p + 4 > BoardLength) break;
                cntWhite = 0, cntBlack = 0;
                for (int u = p, v = k; u <= p + 4; u++, v++) {
                    if (chessBoard[u][v] == White) cntWhite++;
                    else if (chessBoard[u][v] == Black) cntBlack++;
                }
                pointscore += judgeTypeAndGiveScore(cntWhite, cntBlack);
            }
           // printf("%7d\n",pointscore);
        //副对角线搜

            for (int p = i + 4, k = j - 4; k <= j; p--, k++) { //枚举左下端点
                if (k < 0 || p > BoardLength) continue;
                else if (k + 4 > BoardLength || p - 4 < 0) break;
                cntWhite = 0, cntBlack = 0;
                for (int u = p, v = k; v <= k + 4; u--, v++) {

                    if (chessBoard[u][v] == White) cntWhite++;
                    else if (chessBoard[u][v] == Black) cntBlack++;
                }
                pointscore += judgeTypeAndGiveScore(cntWhite, cntBlack);
            }
          //  printf("%7d\n",pointscore);

            printf("%7d",pointscore);
        }
        printf("\n");
    }
}

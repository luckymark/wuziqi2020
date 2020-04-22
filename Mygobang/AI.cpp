//
// Created by 彭琳峰 on 2020/4/21.
//

#include "AI.h"
#include "mainwindow.h"
AI::AI() {
    point.x=-1;
    point.y=-1;
    for (int i = 0; i <BoardLength ; ++i) {
        for (int j = 0; j <BoardLength ; ++j) {
            scoreTable[i][j]=0;
        }
    }
}
void AI::calculateScore(const int chessBoard[15][15]) {
    for (int i = 0; i <BoardLength ; ++i) {
        for (int j = 0; j <BoardLength ; ++j) {
            scoreTable[i][j]=calculateSinglePoint(i,j,chessBoard);
        }
    }
}

Point AI::findBestScore(const int score[15][15])
{
    int bestsocre = -10000;
    Point bestpoint;
    FILE  *fp;
    fp = fopen("log.txt","w+");
    for (int i = 0; i <BoardLength ; ++i) {
        for (int j = 0; j <BoardLength ; ++j) {
            fprintf(fp,"%7d ",score[i][j]);
            if(score[i][j]>bestsocre)
            {
                bestpoint.x=i;
                bestpoint.y=j;
                bestsocre=score[i][j];
            }
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    return bestpoint;
}

int AI::judgeTypeAndGiveScore(const int cntWhite,const int cntBlack) {
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

int AI::calculateSinglePoint(const int i, const int j, const int chessBoard[15][15]) {

    int pointscore=0;
    if (chessBoard[i][j]==0){
        int cntWhite,cntBlack;

        //横向搜
        for (int k =j-4 ; k <=j ; ++k) { //枚举左端点
            if (k<0)
            {
                k=0;
                continue;
            }
            cntWhite=0,cntBlack=0;
            //搜一个小条
            for (int l = k; l <=k+4 ; ++l) {
                if (l>BoardLength) break;
                if(chessBoard[i][l]==White) cntWhite++;
                else if (chessBoard[i][l]==Black) cntBlack++;
            }
            //给这个小条打分
            pointscore+=judgeTypeAndGiveScore(cntWhite,cntBlack);

        }
        //纵向搜
        for (int k =i-4 ; k <=i ; ++k) {  //枚举上端点
            if (k<0)
            {
                k=0;
                continue;
            }
            //搜一个小条
            cntWhite=0,cntBlack=0;
            for (int l = k; l <=k+4 ; ++l) {
                if (l>BoardLength) break;
                if(chessBoard[l][j]==1) cntWhite++;
                else if (chessBoard[l][j]==-1) cntBlack++;
            }
            //给这个小条打分
            pointscore+=judgeTypeAndGiveScore(cntWhite,cntBlack);

        }
        //主对角线搜
        for (int p=i-4,k =j-4; k <=j ; ++k,++p) { //枚举左上端点
            if (k<0||p<0) continue;
            cntWhite=0,cntBlack=0;
            for (int u = p,v=k; u <=p+4 ; u++,v++) {
                if (u>BoardLength||v>BoardLength) break;
                if(chessBoard[u][v]==White) cntWhite++;
                else if (chessBoard[u][v]==Black) cntBlack++;
            }
            pointscore+=judgeTypeAndGiveScore(cntWhite,cntBlack);
        }
        //副对角线搜

        for (int p=i+4,k =j-4 ; k <=j ; p--,k++) { //枚举左下端点
            if (k<0||p>BoardLength) continue;
            cntWhite=0,cntBlack=0;
            for (int u=p, v=k; v<=k+4 ; u--,v++) {
                if (v>BoardLength||u<0) continue;
                if(chessBoard[u][v]==White) cntWhite++;
                else if (chessBoard[u][v]==Black) cntBlack++;
            }
            pointscore+=judgeTypeAndGiveScore(cntWhite,cntBlack);
        }

    }
    return pointscore;
}

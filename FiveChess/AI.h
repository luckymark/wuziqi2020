/**
 * @author Artificial01
 * @date 2020-6-9
 * @version 2.0
 * */

/*
 * 估值函数 evaluate() 的实现：仅简单地运用了数组与循环、运行速度似乎稍慢了一点
 *
 * 原本的递归函数 theDirect() 转化为了 普通函数
 *
 * 原本的递归函数 theColorChessWin() 替换为了 普通函数 theWin()
 *
 * */

#ifndef FIVECHESS_AI_H
#define FIVECHESS_AI_H
#endif

void theDirect(int theBoardData[17][17],int x,int y,int xAdd,int yAdd,int cb[2]);  //某个棋子 在某个射线方向上：cb[0] 储存 count(连续长度)、cb[1] 储存 block(是否堵塞)
int hasNeighbor(int theBoardData[17][17],int x,int y);  //判断并打分 相邻距离 1 棋子
int hasNeighNeighbor(int theBoardData[17][17],int x,int y);  //判断 相邻距离 2 棋子
void PredictChess(int theBoardData[17][17],int theChess[150][2],int deep);  //预测并排序 比较合理的落棋坐标
int theWin(int theBoardData[17][17],int x,int y);  //判断 是否胜利
int evaluate (int theBoardData[17][17]);  //棋局评分
int maxLayer(int theBoardData[17][17],int deep,int alpha,int beta,int x,int y);  //最大层
int minLayer(int theBoardData[17][17],int deep,int alpha,int beta,int x,int y);  //最小层 AI 执白棋 白棋赋值为 -1 AI 希望分数尽可能低
void AI_MaxMin(int theBoardData[17][17],int deep,int * chess_x,int * chess_y);  //AI

void theDirect(int theBoardData[17][17],int x,int y,int xAdd,int yAdd,int cb[2]){
    while (theBoardData[x+xAdd][y+yAdd]==theBoardData[x][y]){
        cb[0]++;
        x+=xAdd;
        y+=yAdd;
    }
    if(x+xAdd>0 && x+xAdd<16 && y+yAdd>0 && y+yAdd<16 && theBoardData[x+xAdd][y+yAdd]==0) cb[1]=0;
}

int hasNeighbor(int theBoardData[17][17],int x,int y){
    int count,level=0;
    int add[8][2]={{-1,1},{0,1},{1,1},{-1,0},{1,0},{-1,-1},{0,-1},{1,-1}};
    for(int i=0;i<8;i++)
        if(theBoardData[x+add[i][0]][y+add[i][1]]){
            theBoardData[x][y]=theBoardData[x+add[i][0]][y+add[i][1]];
            int countAndBlock1[2] = {0, 1}, countAndBlock2[2] = {0, 1};
            theDirect(theBoardData, x, y, add[i][0], add[i][1], countAndBlock1);
            theDirect(theBoardData, x, y, -add[i][0], -add[i][1], countAndBlock2);
            theBoardData[x][y]=0;
            count=2+countAndBlock1[0]+countAndBlock2[0]-countAndBlock1[1]-countAndBlock2[1];  //这里 2+ 使得 max 必不为零 以此区别是否有邻居
            if(count>level) level=count;
        }
    return level;
}

/*int hasNeighNeighbor(int theBoardData[17][17],int x,int y){  //运行有些慢、作用不大 于是被我注释掉了
    int neighbor_x,neighbor_y;
    int add[16][2]={{-2,2},{-1,2},{0,2},{1,2},{2,2},{-2,-2},{-1,-2},{0,-2},{1,-2},{2,-2},{-2,1},{-2,0},{-2,-1},{2,1},{2,0},{2,-1}};
    for(int i=0;i<16;i++){
        neighbor_x=x+add[i][0];
        neighbor_y=y+add[i][1];
        if(neighbor_x>0 && neighbor_x<16 && neighbor_y>0 && neighbor_y<16 && theBoardData[neighbor_x][neighbor_y]) return 1;
    }
    return 0;
}*/

int hasNeighNeighbor(int theBoardData[17][17],int x,int y){
    return 0;
}

void PredictChess(int theBoardData[17][17],int theChess[150][2],int deep){
    int level;
    int Chess[6][50][2];
    int Count[6]={0,0,0,0,0,0},theCount=1;
    for(int i=1;i<=15;i++)
        for(int j=1;j<=15;j++) {
            if (theBoardData[i][j] == 0) {
                level = hasNeighbor(theBoardData, i, j);
                if (level == 0) {
                    if(deep > 4 && hasNeighNeighbor(theBoardData, i, j)){
                        Chess[0][Count[0]][0] = i;
                        Chess[0][Count[0]][1] = j;
                        Count[0]++;
                    }
                } else if (level < 5) {
                    Chess[level][Count[level]][0] = i;
                    Chess[level][Count[level]][1] = j;
                    Count[level]++;
                } else {
                    Chess[5][Count[5]][0] = i;
                    Chess[5][Count[5]][1] = j;
                    Count[5]++;
                }
            }
        }
    for(int i=5;i>=0;i--) {
        for (int j = 0; j < Count[i]; j++) {
            theChess[theCount][0] = Chess[i][j][0];
            theChess[theCount][1] = Chess[i][j][1];
            theCount++;
        }
    }
    theChess[0][0]=theCount;
}

int theWin(int theBoardData[17][17],int x,int y){
    int add[4][2]={{1,0},{1,1},{0,1},{-1,1}};
    for(int i=0;i<4;i++){
        int count=0;
        int temp_x=x,temp_y=y;
        while (theBoardData[temp_x][temp_y]==theBoardData[temp_x+add[i][0]][temp_y+add[i][1]]){
            count++;
            temp_x+=add[i][0];
            temp_y+=add[i][1];
        }
        temp_x=x,temp_y=y;
        while (theBoardData[temp_x][temp_y]==theBoardData[temp_x-add[i][0]][temp_y-add[i][1]]){
            count++;
            temp_x-=add[i][0];
            temp_y-=add[i][1];
        }
        if(count>=4) return 1;
    }
    return 0;
}

int evaluate (int theBoardData[17][17]){
    int score=0;
    int add[4][2]={{1,0},{1,1},{0,1},{-1,1}};
    for(int i=1;i<=15;i++)
        for(int j=1;j<=15;j++)
            if(theBoardData[i][j]){
                for(int k=0;k<4;k++) {
                    int countAndBlock1[2] = {0, 1}, countAndBlock2[2] = {0, 1};
                    theDirect(theBoardData, i, j, add[k][0], add[k][1], countAndBlock1);
                    theDirect(theBoardData, i, j, -add[k][0], -add[k][1], countAndBlock2);
                    if (countAndBlock1[1] + countAndBlock2[1] == 0) {
                        switch (countAndBlock1[0] + countAndBlock2[0]) {
                            case 0:
                                score += theBoardData[i][j];
                                break;
                            case 1:
                                score += 5*theBoardData[i][j];
                                break;
                            case 2:
                                score += 400*theBoardData[i][j];
                                break;
                            default:
                                score += 4000*theBoardData[i][j];
                                break;
                        }
                    } else if (countAndBlock1[1] + countAndBlock2[1] == 1) {
                        switch (countAndBlock1[0] + countAndBlock2[0]) {
                            case 0:
                                break;
                            case 1:
                                score += theBoardData[i][j];
                                break;
                            case 2:
                                score += 3*theBoardData[i][j];
                                break;
                            case 3:
                                score += 200*theBoardData[i][j];
                                break;
                            default:
                                score += 4000*theBoardData[i][j];
                                break;
                        }
                    } else if (countAndBlock1[0] + countAndBlock2[0]>=4) score += 4000*theBoardData[i][j];
                }
            }
    return score;
}

int maxLayer(int theBoardData[17][17],int deep,int alpha,int beta,int x,int y){
    if(deep==0 || theWin(theBoardData,x,y)) return evaluate(theBoardData);
    int best=-10000000;
    int validChess[150][2];
    PredictChess(theBoardData,validChess,deep);
    for(int i=1;i<validChess[0][0];i++){
        theBoardData[validChess[i][0]][validChess[i][1]]=1;
        int boardScore=minLayer(theBoardData,deep-1,alpha,(best>beta)*(best-beta)+beta,validChess[i][0],validChess[i][1]);  //把三目运算替换了一下
        theBoardData[validChess[i][0]][validChess[i][1]]=0;
        if(boardScore>alpha) return boardScore;
        if(boardScore>best) best=boardScore;
    }
    return best;
}

int minLayer(int theBoardData[17][17],int deep,int alpha,int beta,int x,int y){
    if(deep==0 || theWin(theBoardData,x,y)) return evaluate(theBoardData);
    int best=10000000;
    int validChess[150][2];
    PredictChess(theBoardData,validChess,deep);
    for(int i=1;i<validChess[0][0];i++){
        theBoardData[validChess[i][0]][validChess[i][1]]=-1;
        int boardScore=maxLayer(theBoardData,deep-1,(best<alpha)*(best-alpha)+alpha,beta,validChess[i][0],validChess[i][1]);
        theBoardData[validChess[i][0]][validChess[i][1]]=0;
        if(boardScore<beta) return boardScore;
        if(boardScore<best) best=boardScore;
    }
    return best;
}

void AI_MaxMin(int theBoardData[17][17],int deep,int * chess_x,int * chess_y){
    int best=10000000;
    int validChess[150][2];
    PredictChess(theBoardData,validChess,deep);
    for(int i=1;i<validChess[0][0];i++){
        theBoardData[validChess[i][0]][validChess[i][1]]=-1;
        int boardScore=maxLayer(theBoardData,deep-1,best,-10000000,validChess[i][0],validChess[i][1]);
        theBoardData[validChess[i][0]][validChess[i][1]]=0;
        if(boardScore<best){
            (*chess_x)=validChess[i][0];
            (*chess_y)=validChess[i][1];
            best=boardScore;
        }
    }
}

/**
 *
 * 变量类型 主要是数组
 * 函数 主要是递归函数 (然而 似乎好像大概 一些功能用递归函数实现 虽然代码很短 但是运行会比较慢)
 *
 * 注释 介绍了函数功能 没有介绍函数具体实现方式
 *
 * 潜在问题：hasNeighbor() 只考虑了距离为 1 (这样做 是因为 6层层数比较低 导致 距离为2的作用太小(下了很多局之后的总结)而运算量太大)
 *
 * 棋盘感觉比较好看 但不知道为什么 运行复制到git管理的文件夹下后的源代码时 会出现乱码 而 运行被复制的那份源代码时 没有问题
 * 棋盘 竖向为 x 横向为 y
 *
 * 这个项目只有这一篇代码 基本功能已经完备 还会修改 暂时提交一下
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <synchapi.h>
#include <locale.h>

#define DEEP 6  //层数

int boardData[17][17],place_x,place_y,turn;  //棋盘棋子的信息(这里采用 17*17 是为了方便 实际是 15*15(0号与16号 不用))、落棋的坐标、当前的执棋者

void initBoard();  //初始化棋盘
void drawBoard();  //打印棋盘棋子
int theDirectCount(int x,int y,int xAdd,int yAdd,int count);  //某个棋子 在某个射线方向上 的连续长度
int theColorChessWin();  //判断 是否胜利 以及 哪方胜利
void ifWin();  //胜利之后 的程序结束处理
void turnSwitch();  //交换 执棋者
void placeChess();  //玩家 以及 AI 下棋操作

void theDirect(int theBoardData[17][17],int x,int y,int xAdd,int yAdd,int cb[2]);  //某个棋子 在某个射线方向上：cb[0] 储存 count(连续长度)、cb[1] 储存 block(是否堵塞)
int hasNeighbor(int theBoardData[17][17],int x,int y);  //判断并打分 相邻棋子
void PredictChess(int theBoardData[17][17],int theChess[150][2]);  //预测并排序 比较合理的落棋坐标
int evaluate (int theBoardData[17][17]);  //棋局评分
int maxLayer(int theBoardData[17][17],int deep,int alpha,int beta);  //最大层
int minLayer(int theBoardData[17][17],int deep,int alpha,int beta);  //最小层 AI 执白棋 白棋赋值为 -1 AI 希望分数尽可能低
void AI_MaxMin(int theBoardData[17][17],int deep,int * chess_x,int * chess_y);  //AI

int main() {
    initBoard();
    for(;;){
        drawBoard();
        ifWin();
        turnSwitch();
        placeChess();
        system("cls");
    }
}


void initBoard(){
    memset(boardData,0,17*17* sizeof(int));
    turn=-1;
    place_x=0,place_y=0;
    system("cls");
    printf("Welcome!\n");
    Sleep(1000);
    system("cls");
}

void drawBoard(){
    setlocale(LC_ALL,"chs");
    wchar_t black=L'○',white=L'●',nothing=L'·';
    printf("\n");
    for(int i=0;i<10;i++)
        printf(" 0%d",i);
    for(int i=10;i<17;i++)
        printf(" %d",i);
    printf("\n");
    for(int i=1;i<10;i++){
        printf(" 0%d",i);
        for(int j=1;j<=15;j++){
            if(boardData[i][j]==1) wprintf(L" %c ",black);
            else if (boardData[i][j]==-1) wprintf(L" %c ",white);
            else wprintf(L" %c ",nothing);
        }
        printf(" 0%d\n",i);
    }
    for(int i=10;i<16;i++){
        printf(" %d",i);
        for(int j=1;j<=15;j++){
            if(boardData[i][j]==1) wprintf(L" %c ",black);
            else if (boardData[i][j]==-1) wprintf(L" %c ",white);
            else wprintf(L" %c ",nothing);
        }
        printf(" %d\n",i);
    }
    for(int i=0;i<10;i++)
        printf(" 0%d",i);
    for(int i=10;i<17;i++)
        printf(" %d",i);
    wprintf(L"\n (Black-> %c | White-> %c)\n\n",black,white);
}

int theDirectCount(int x,int y,int xAdd,int yAdd,int count){
    if(x>0 && x<16 && y>0 && y<16 && boardData[x+xAdd][y+yAdd]==boardData[x][y]) return theDirectCount(x+xAdd,y+yAdd,xAdd,yAdd,++count);
    else return count;
}

int theColorChessWin(){
    int add[4][2]={{1,0},{1,1},{0,1},{-1,1}};
    for(int i=0;i<4;i++)
        if((theDirectCount(place_x,place_y,add[i][0],add[i][1],0) + theDirectCount(place_x,place_y,-add[i][0],-add[i][1],0))>=4) return boardData[place_x][place_y];
    return 0;
}

void ifWin(){
    if(theColorChessWin()==1){
        printf("Congratulations! Black chess player win!");
        exit(0);
    } else if (theColorChessWin()==-1){
        printf("White chess player win!");
        exit(0);
    }
}

void turnSwitch(){
    if(turn==1) turn=-1;
    else turn=1;
}

void placeChess(){
    if(turn==1){
        printf("It is turn to Black chess player\n");
        do{
            printf("Input x and y:");
            scanf(" %d %d",&place_x,&place_y);
        }while (place_x<=0 || place_x>=16 || place_y<=0 || place_y>=16 || boardData[place_x][place_y]!=0);
    }else{
        printf("It is turn to White chess player\n");
        AI_MaxMin(boardData,DEEP,&place_x,&place_y);
    }
    boardData[place_x][place_y]=turn;
}

void theDirect(int theBoardData[17][17],int x,int y,int xAdd,int yAdd,int cb[2]){
    if(x>0 && x<16 && y>0 && y<16 && theBoardData[x+xAdd][y+yAdd]==theBoardData[x][y]){
        cb[0]++;
        theDirect(theBoardData,x+xAdd,y+yAdd,xAdd,yAdd,cb);
    }else if(x+xAdd>0 && x+xAdd<16 && y+yAdd>0 && y+yAdd<16 && theBoardData[x+xAdd][y+yAdd]==0) cb[1]=0;
}

int hasNeighbor(int theBoardData[17][17],int x,int y){
    int level=0;
    int add[8][2]={{-1,1},{0,1},{1,1},{-1,0},{1,0},{-1,-1},{0,-1},{1,-1}};
    for(int i=0;i<8;i++)
        if(theBoardData[x+add[i][0]][y+add[i][1]]){
            theBoardData[x][y]=theBoardData[x+add[i][0]][y+add[i][1]];
            int countAndBlock1[2] = {0, 1}, countAndBlock2[2] = {0, 1};
            theDirect(theBoardData, x, y, add[i][0], add[i][1], countAndBlock1);
            theDirect(theBoardData, x, y, -add[i][0], -add[i][1], countAndBlock2);
            int count=2+countAndBlock1[0]+countAndBlock2[0]-countAndBlock1[1]-countAndBlock2[1];  //这里 2+ 使得 max 必不为零 以此区别是否有邻居
            if(count>level) level=count;
            theBoardData[x][y]=0;
        }
    return level;
}

void PredictChess(int theBoardData[17][17],int theChess[150][2]){
    int Chess1[5][50][2],Chess2[50][2];
    int Count1[5]={0,0,0,0,0},Count2=0,theCount=1;
    for(int i=1;i<=15;i++)
        for(int j=1;j<=15;j++)
            if(theBoardData[i][j]==0) {
                int level=hasNeighbor(theBoardData, i, j);
                if(level==1) {
                    Chess1[0][Count1[0]][0] = i;
                    Chess1[0][Count1[0]][1] = j;
                    Count1[0]++;
                } else if (level==2) {
                    Chess1[1][Count1[1]][0] = i;
                    Chess1[1][Count1[1]][1] = j;
                    Count1[1]++;
                } else if (level==3) {
                    Chess1[2][Count1[2]][0] = i;
                    Chess1[2][Count1[2]][1] = j;
                    Count1[2]++;
                } else if (level==4) {
                    Chess1[3][Count1[3]][0] = i;
                    Chess1[3][Count1[3]][1] = j;
                    Count1[3]++;
                } else if (level>=5) {
                    Chess1[4][Count1[4]][0] = i;
                    Chess1[4][Count1[4]][1] = j;
                    Count1[4]++;
                }
            }
    for(int i=4;i>=0;i--) {
        for (int j = 0; j < Count1[i]; j++) {
            theChess[theCount][0] = Chess1[i][j][0];
            theChess[theCount][1] = Chess1[i][j][1];
            theCount++;
        }
    }
    for(int i=0;i<Count2;i++){
        theChess[theCount][0]=Chess2[i][0];
        theChess[theCount][1]=Chess2[i][1];
        theCount++;
    }
    theChess[0][0]=theCount;
}

int evaluate (int theBoardData[17][17]){
    int add[4][2]={{1,0},{1,1},{0,1},{-1,1}};
    int score=0;
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
                                score += 300*theBoardData[i][j];
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

int maxLayer(int theBoardData[17][17],int deep,int alpha,int beta){
    if(deep==0 || theColorChessWin()) return evaluate(theBoardData);
    int best=-10000000;
    int validChess[150][2];
    PredictChess(theBoardData,validChess);
    for(int i=1;i<validChess[0][0];i++){
        theBoardData[validChess[i][0]][validChess[i][1]]=1;
        int boardScore=minLayer(theBoardData,deep-1,alpha,best>beta ? best:beta);
        theBoardData[validChess[i][0]][validChess[i][1]]=0;
        if(boardScore>alpha) return boardScore;
        if(boardScore>best) best=boardScore;
    }
    return best;
}

int minLayer(int theBoardData[17][17],int deep,int alpha,int beta){
    if(deep==0 || theColorChessWin()) return evaluate(theBoardData);
    int best=10000000;
    int validChess[150][2];
    PredictChess(theBoardData,validChess);
    for(int i=1;i<validChess[0][0];i++){
        theBoardData[validChess[i][0]][validChess[i][1]]=-1;
        int boardScore=maxLayer(theBoardData,deep-1,best<alpha ? best:alpha,beta);
        theBoardData[validChess[i][0]][validChess[i][1]]=0;
        if(boardScore<beta) return boardScore;
        if(boardScore<best) best=boardScore;
    }
    return best;
}

void AI_MaxMin(int theBoardData[17][17],int deep,int * chess_x,int * chess_y){
    int best=10000000;
    int validChess[150][2];
    PredictChess(theBoardData,validChess);
    for(int i=1;i<validChess[0][0];i++){
        theBoardData[validChess[i][0]][validChess[i][1]]=-1;
        int boardScore=maxLayer(theBoardData,deep-1,best,-10000000);
        theBoardData[validChess[i][0]][validChess[i][1]]=0;
        if(boardScore<best){
            (*chess_x)=validChess[i][0];
            (*chess_y)=validChess[i][1];
            best=boardScore;
        }
    }
}

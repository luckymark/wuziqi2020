#include <utility>
#include <stdlib.h>
#include <time.h>
#include "GameModel.h"
GameModel::GameModel()
{
}
void GameModel::startGame(GameType type)
{
    gameType=type;
    gmVc.clear();
    for(int i=0;i<brdSz;i++){
        std::vector<int> lnBrd;
        for (int j=0;j<brdSz;j++)
            lnBrd.push_back(0);
        gmVc.push_back(lnBrd);
    }
    if (gameType==BOT){
        scVc.clear();
        for(int i=0;i<brdSz;i++)
        {
            std::vector<int> lnSc;
            for(int j=0;j<brdSz;j++)
                lnSc.push_back(0);
            scVc.push_back(lnSc);
        }
    }
    plOpt=true;
}
void GameModel::MapUpd(int row,int col)
{
    if(plOpt)
        gmVc[row][col]=1;
    else
        gmVc[row][col]=-1;
    plOpt=!plOpt;        // 换手
}
void GameModel::PlayerAct(int row,int col)
{
    MapUpd(row,col);
}
void GameModel::AIAct(int &clkRow,int &clkCol)
{
    scrCal();      // 计算评分
    int maxSc=0;
    std::vector<std::pair<int,int>> maxPnt;
    for(int row=1;row<brdSz;row++)
        for(int col=1;col<brdSz;col++){
            if(gmVc[row][col]==0){
                if(scVc[row][col]>maxSc){
                    maxPnt.clear();
                    maxSc=scVc[row][col];
                    maxPnt.push_back(std::make_pair(row,col));
                }
                else if(scVc[row][col]==maxSc)
                    maxPnt.push_back(std::make_pair(row,col));
            }
        }
    srand((unsigned)time(0));
    int index=rand()%maxPnt.size();
    std::pair<int, int> pntPr=maxPnt.at(index);
    clkRow=pntPr.first;
    clkCol=pntPr.second;
    MapUpd(clkRow, clkCol);
}
void GameModel::scrCal()
{
    int plyerNum=0; // 玩家连子的个数
    int AINum=0; // 电脑连子的个数
    int emNum=0;
    scVc.clear();
    for(int i=0;i<brdSz;i++){
        std::vector<int> lineScores;
        for (int j=0;j<brdSz;j++)
            lineScores.push_back(0);
        scVc.push_back(lineScores);
    }
    for(int row=0;row<brdSz;row++)
        for(int col=0;col<brdSz;col++){
            if(row>0&&col>0&&gmVc[row][col]==0){
                for(int y=-1;y<=1;y++)
                    for(int x=-1;x<=1;x++){
                        plyerNum=0;
                        AINum=0;
                        emNum=0;
                        if(!(y==0&&x==0)){
                            for(int i=1;i<=4;i++){
                                if(row+i*y>0&&row+i*y<brdSz&&col+i*x>0&&col+i*x<brdSz&&gmVc[row+i*y][col+i*x]==1){
                                    plyerNum++;
                                }
                                else if(row+i*y>0&&row+i*y<brdSz&&col+i*x>0&&col+i*x<brdSz&&gmVc[row+i*y][col+i*x]==0){
                                    emNum++;
                                    break;
                                }
                                else
                                    break;
                            }
                            for(int i=1;i<=4;i++){
                                if(row-i*y>0&&row-i*y<brdSz&&col-i*x>0&&col-i*x<brdSz&&gmVc[row-i*y][col-i*x]==1){
                                    plyerNum++;
                                }
                                else if(row-i*y>0&&row-i*y<brdSz&&col-i*x>0&&col-i*x<brdSz&&gmVc[row-i*y][col-i*x]==0){
                                    emNum++;
                                    break;
                                }
                                else
                                    break;
                            }
                            if(plyerNum==1)                      // 杀棋
                                scVc[row][col]+=10;
                            else if(plyerNum==2){
                                if(emNum==1)
                                    scVc[row][col]+=30;
                                else if(emNum==2)
                                    scVc[row][col]+=40;
                            }
                            else if(plyerNum==3){
                                if(emNum==1)
                                    scVc[row][col]+=60;
                                else if(emNum==2)
                                    scVc[row][col]+=110;
                            }
                            else if(plyerNum==4)
                                scVc[row][col]+=10100;
                            emNum=0;
                            for(int i=1;i<=4;i++)
                            {
                                if(row+i*y>0&&row+i*y<brdSz&&col+i*x>0&&col+i*x<brdSz&&gmVc[row+i*y][col+i*x]==1){
                                    AINum++;
                                }
                                else if(row+i*y>0&&row+i*y<brdSz&&col+i*x>0&&col+i*x<brdSz&&gmVc[row+i*y][col+i*x]==0){
                                    emNum++;
                                    break;
                                }
                                else
                                    break;
                            }

                            for(int i=1;i<=4;i++){
                                if(row-i*y>0&&row-i*y<brdSz&&col-i*x>0&&col-i*x<brdSz&&gmVc[row-i*y][col-i*x]==-1){
                                    AINum++;
                                }
                                else if(row-i*y>0&&row-i*y<brdSz&&col-i*x>0&&col-i*x<brdSz&&gmVc[row-i*y][col-i*x]==0){
                                    emNum++;
                                    break;
                                }
                                else
                                    break;
                            }
                            if(AINum==0)                       //死二
                                scVc[row][col]+=10;
                            else if(AINum==1)                  // 活二
                                scVc[row][col]+=100;
                            else if(AINum==2){
                                if (emNum==1)                  // 死三
                                    scVc[row][col]+=100;
                                else if(emNum==2)
                                    scVc[row][col]+=1000;      // 活三
                            }
                            else if(AINum==3){
                                if(emNum==1)                   // 死四
                                    scVc[row][col]+=1000;
                                else if(emNum==2)
                                    scVc[row][col]+=10000;     // 活四
                            }
                            else if(AINum>=4)
                                scVc[row][col]+=100000;        // 活五

                        }
                    }

            }
        }
}

bool GameModel::isWin(int row,int col)
{
    for (int i=0;i<5;i++){                        //判断是否分出胜负
        if(col-i>0&&col-i+4<brdSz&&gmVc[row][col-i]==gmVc[row][col-i+1]&&gmVc[row][col-i]==gmVc[row][col-i+2]&&gmVc[row][col-i]==gmVc[row][col-i+3]&&gmVc[row][col-i]==gmVc[row][col-i+4])
           return true;
    }
    for(int i=0;i<5;i++){
        if(row-i>0&&row-i+4<brdSz&&gmVc[row-i][col]==gmVc[row-i+1][col]&&gmVc[row-i][col]==gmVc[row-i+2][col]&&gmVc[row-i][col]==gmVc[row-i+3][col]&&gmVc[row-i][col]==gmVc[row-i+4][col])
           return true;
    }
    for(int i=0;i<5;i++){
        if(row+i<brdSz&&row+i-4>0&&col-i>0&&col-i+4<brdSz&&gmVc[row+i][col-i]==gmVc[row+i-1][col-i+1]&&gmVc[row+i][col-i]==gmVc[row+i-2][col-i+2]&&gmVc[row+i][col-i]==gmVc[row+i-3][col-i+3]&&gmVc[row+i][col-i]==gmVc[row+i-4][col-i+4])
           return true;
    }
    for(int i=0;i<5;i++){
        if(row-i>0&&row-i+4<brdSz&&col-i>0&&col-i+4<brdSz&&gmVc[row-i][col-i]==gmVc[row-i+1][col-i+1]&&gmVc[row-i][col-i]==gmVc[row-i+2][col-i+2]&&gmVc[row-i][col-i]==gmVc[row-i+3][col-i+3]&&gmVc[row-i][col-i]==gmVc[row-i+4][col-i+4])
           return true;
    }
    return false;
}

bool GameModel::isDead()
{
    for(int i=1;i<brdSz;i++)
        for(int j=1;j<brdSz;j++){
            if(!(gmVc[i][j]==1||gmVc[i][j]==-1))
               return false;
        }
    return true;
}

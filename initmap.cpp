#pragma GCC optimize(3)
#pragma G++ optimize(3)
#include"evaluator.h"
#include<QDebug>
int weight[5][2][2];
void Evaluator::initMap()
{
    initWeight();
    memBlack.clear();
    memWhite.clear();
    mapBlack.clear();
    mapWhite.clear();
    initMapBlack();
    initMapWhite();
    //qDebug()<<mapBlack.size()+mapWhite.size();
}
void Evaluator::initWeight()
{
    //1st is win/lose or 1 2 3 4
    //2nd is flex 0 block 1
    //3rd is white 0 black 1
    weight[0][0][0]=weight[0][1][0]=M_WIN;
    weight[0][0][1]=weight[0][1][1]=M_lose;
    weight[1][0][0]=M_FLEX1;
    weight[2][0][0]=M_FLEX2;
    weight[3][0][0]=M_FLEX3;
    weight[4][0][0]=M_FLEX4;
    weight[2][1][0]=M_BLOCK2;
    weight[3][1][0]=M_BLOCK3;
    weight[4][1][0]=M_BLOCK4;

    weight[1][0][1]=M_flex1;
    weight[2][0][1]=M_flex2;
    weight[3][0][1]=M_flex3;
    weight[4][0][1]=M_flex4;
    weight[2][1][1]=M_block2;
    weight[3][1][1]=M_block3;
    weight[4][1][1]=M_block4;
}
void Evaluator::initMapWhite()
{
    //连5
    mapWhite["11111"]=weight[0][0][0];
    //冲4
    mapWhite["11101"]=weight[4][1][0];
    mapWhite["11011"]=weight[4][1][0];
    mapWhite["10111"]=weight[4][1][0];

    mapWhite["11110"]=weight[4][1][0];
    mapWhite["01111"]=weight[4][1][0];

    initMap(3,"11101",1,0);
    initMap(3,"11011",1,0);
    initMap(3,"10111",1,0);

    initMap(3,"11110",1,0);
    initMap(3,"01111",1,0);

    //活4
    mapWhite["011110"]=weight[4][0][0];
    initMap(3,"011110",0,0);
}
void Evaluator::initMapBlack()
{

    //连5
    mapBlack["22222"]=weight[0][0][1];

    //冲4
    mapBlack["22202"]=weight[4][1][1];
    mapBlack["22022"]=weight[4][1][1];
    mapBlack["20222"]=weight[4][1][1];

    mapBlack["22220"]=weight[4][1][1];
    mapBlack["02222"]=weight[4][1][1];


    initMap(3,"22202",1,1);
    initMap(3,"22022",1,1);
    initMap(3,"20222",1,1);

    initMap(3,"22220",1,1);
    initMap(3,"02222",1,1);

    //活4
    mapBlack["022220"]=weight[4][0][1];
    initMap(3,"022220",0,1);
}
void Evaluator::initMap(int level, string str,bool isBlock, bool isBlack)
{
    //str have level+1 elements
    if(1==level&&isBlock)return;
    for(unsigned i=0;i<str.size();++i){
        if(bool2str(isBlack)==str[i]){
            str[i]='0';
            if(isBlack){
                mapBlack[str]=weight[level][isBlock][1];
            }
            else{
                mapWhite[str]=weight[level][isBlock][0];
            }
            if(level!=1)initMap(level-1,str,isBlock,isBlack);
            str[i]=bool2str(isBlack);
        }
    }
}

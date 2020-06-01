#pragma GCC optimize(3)
#pragma G++ optimize(3)
#include"evaluator.h"
#include<QDebug>
int weight[5][2][2];
void Evaluator::initMap()
{
    memBlack.clear();
    memWhite.clear();
    mapBlack.clear();
    mapWhite.clear();
    initWeight();
    initMapBlack();
    initMapWhite();
//    qDebug()<<mapBlack.size()+mapWhite.size();
    //输出结果表明，目前有82个棋形
    //最初的确有400多种棋形，可以理解为这里把一些相近的棋形合并了
    //即权衡精度和时间常数
}
void Evaluator::initWeight()
{
    //第一维是分值等级
    //第二维是活（0）还是眠(1)类型
    //第三维是白(0)还是黑(1)

    //显然weight里面存放的是各个宏值
    //使用数组是为了方便递归时能利用参数取出宏值
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
    //手动完成4，5，剩下递归生成。
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

    //手动完成4，5，剩下递归生成。
}
void Evaluator::initMap(int level, string str,bool isBlock, bool isBlack)
{

    if(1==level&&isBlock)return;//因为我没有对眠1打分
    for(unsigned i=0;i<str.size();++i){
        if(bool2str(isBlack)==str[i]){
            str[i]='0';
            //减少一颗有利棋子
            if(isBlack){
                mapBlack[str]=weight[level][isBlock][1];
            }
            else{
                mapWhite[str]=weight[level][isBlock][0];
            }
            if(level!=1)initMap(level-1,str,isBlock,isBlack);
            str[i]=bool2str(isBlack);
            //回溯
        }
    }
}

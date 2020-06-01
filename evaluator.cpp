#pragma GCC optimize(3)
#pragma G++ optimize(3)
#include "evaluator.h"
#include "def.h"
#include"utility.h"
#include"gobang.h"
#include"ui_widget.h"

Evaluator::Evaluator(GoBang *parent)
{
    this->parent=parent;
    init();
}
void Evaluator::init()
{
    initMap();
    memset(need, 0, sizeof need);
}
int Evaluator::greedy_search(int color){
    int bestMark=(color==C_BLACK)?INT_MAX:INT_MIN;
    //黑子希望分数小，白子希望分数大，这里初始化为反向的最值
    int &bmark=bestMark;
    //我发现了一种新的写注释方法hhhh
    int mark,markBlack,markWhite;

    for(int i=0;i<NUMBER;++i){
        for(int j=0;j<NUMBER;++j){
            if(isNeed(i,j)&&C_EMPTY==getEle(i,j)){
                getEle(i,j)=color;

                markWhite=getScore(mapWhite);
                markBlack=getScore(mapBlack);
                mark=markWhite-markBlack;
                //得分为两者得分之差
                if(markWhite>=M_WIN&&markBlack<M_lose)mark=INT_MAX;
                if(markWhite<M_WIN&&markBlack>=M_lose)mark=INT_MIN;
                //考虑在某种得分下，其中一方其实已经胜利的情况

                getEle(i,j)=C_EMPTY;
                bmark=(color==C_BLACK)?min(bmark,mark):max(bmark,mark);
            }
        }
    }
    return bmark;
}


int Evaluator::max_min_search(int col, int alpha, int beta, int depth){
    if(MAX_LEVEL==depth)
        return greedy_search(C_BLACK);
    //最后一层贪心搜索
    int bestMark,mark;
    bestMark=(depth&1)?INT_MIN:INT_MAX;
    //偶数层希望分数小，奇数层希望分数大，这里初始化为反向的最值
    if (alpha>=beta)return bestMark;
    //alpha-beta剪枝
    NBig Q;getNBig(Q,depth,col);
    //获得搜索的候选节点
    while(Q.size()){
        const Node &temp=Q.pop();
        getEle(temp.row,temp.col)=col;
        mark=max_min_search(C_BLACK+C_WHITE-col,alpha,beta,depth+1);
        //两层之间颜色交替
        getEle(temp.row,temp.col)=C_EMPTY;
        //回溯
        if(depth&1){
            bestMark=max(bestMark,mark);
            alpha=max(alpha,mark);
        }
        else{
            bestMark=min(bestMark,mark);
            beta=min(beta,mark);
        }
        if(alpha>=beta)return bestMark;
        //ab剪枝
    }
    return bestMark;
}
void Evaluator::getNBig(NBig& Q,int depth,int col){
    Q.clear();
    for(int i=0;i<NUMBER;++i){
        for(int j=0;j<NUMBER;++j){
            //贪心地寻找候选人

            if(isNeed(i,j)&&C_EMPTY==getEle(i,j)){
                getEle(i,j)=col;

                int markWhite=getScore(mapWhite);
                int markBlack=getScore(mapBlack);
                int mark=markWhite-markBlack;
                //一步必胜或者必败
                if(depth&1){
                    //AI
                    if(markBlack>=M_lose&&markWhite<M_WIN)mark=INT_MIN;
                    if(markBlack<M_lose&&markWhite>=M_WIN)mark=INT_MAX;
                }
                else{
                    //human
                    if(markBlack<M_lose&&markWhite>=M_WIN)mark=INT_MAX;
                    if(markBlack>=M_lose&&markWhite<M_WIN)mark=INT_MIN;
                }

                getEle(i,j)=C_EMPTY;
                //回溯
                if(depth&1)Q.push(Node(mark,i,j));
                else Q.push(Node(-1*mark,i,j));
                //abs(INT_MAX)<abs(INT_MIN)所以不用考虑溢出
                //奇数层要求分值大在前
                //偶数层要求分值小在前
            }

        }
    }
}
int Evaluator::getScore(const map<string,int> &mp)const
{
    int mark=0;
    string temp;
    temp.reserve(unsigned(NUMBER+3));
    //减少重新分配空间的开销
    //每列
    for(int i=0;i<NUMBER;++i){
        for(int j=0;j<NUMBER;++j){
            if(0==j)temp="3";
            temp+=int2char(getEle(i,j));
            if((NUMBER-1)==j)temp+="3";
        }
        mark+=matchString(temp,mp);
    }

    //每行
    for(int i=0;i<NUMBER;++i){
        for(int j=0;j<NUMBER;++j){
            if(0==j)temp="3";
            temp+=int2char(getEle(j,i));
            if((NUMBER-1)==j)temp+="3";
        }
        mark+=matchString(temp,mp);
    }

    {
        //主对角线
        for(int i=0;i<NUMBER;++i){
            if(0==i)temp="3";
            temp+=int2char(getEle(i,i));
            if(NUMBER-1==i)temp+="3";

        }
        mark+=matchString(temp,mp);
        //主上三角
        for(int k=1;k<NUMBER;++k){
            for(int i=0,j=k;j<NUMBER;++i,++j){
                if(0==i)temp="3";
                temp+=int2char(getEle(i,j));
                if(NUMBER-1==j)temp+="3";
            }
            mark+=matchString(temp,mp);
        }
        //主下三角
        for(int k=1;k<NUMBER;++k){
            for(int i=0,j=k;j<NUMBER;++i,++j){
                if(0==i)temp="3";
                temp+=int2char(getEle(j,i));
                if(NUMBER-1==j)temp+="3";
            }
            mark+=matchString(temp,mp);
        }
    }

    {
        //次对角线
        for(int i=0;i<NUMBER;++i){
            if(0==i)temp="3";
            temp+=int2char(getEle(i,NUMBER-1-i));
            if(NUMBER-1==i)temp+="3";
        }
        mark+=matchString(temp,mp);
        //次上三角
        for(int k=0;k<NUMBER-1;++k){
            for(int i=0;i<=k;++i){
                if(0==i)temp="3";
                temp+=int2char(getEle(i,k-i));
                if(0==k-i)temp+="3";
            }
            mark+=matchString(temp,mp);
        }
        //次下三角
        for(int k=NUMBER;k<=2*NUMBER-2;++k){
            for(int j=NUMBER-1;(k-j)<NUMBER;--j){
                if(NUMBER-1==j)temp="3";
                temp+=int2char(getEle(k-j,j));
                if(NUMBER-1==k-j)temp+="3";
            }
            mark+=matchString(temp,mp);
        }
    }
    return mark;
}

int Evaluator::matchString(string &str,const map<string,int> &mp)const
{
    if(&mp==&mapWhite){
        if(memWhite.count(str)){
            return memWhite[str];
        }
    }
    else{
        if(memBlack.count(str)){
            return memBlack[str];
        }
    }
    //记忆化

    int sum=0;
    for(auto itr=mp.begin();itr!=mp.end();++itr){
        //遍历每种棋形
        unsigned long long index=0;
        //可能同一个棋形会出现多次，这里循环调用find函数
        while(  (index=str.find(itr->first,index))<str.length()  ){
            ++index;
            sum+=itr->second;
        }
    }

    if(&mp==&mapWhite){
        memWhite[str]=sum;
    }
    else{
        memBlack[str]=sum;
    }
    return sum;
    //记忆化
}
bool Evaluator::checkTie()const
{
    //棋盘是否被下满
    if(parent->counter==NUMBER*NUMBER)return 1;
    return 0;
}

int Evaluator::check(int col)const
{
    if(checkTie())return S_TIE;
    //平局
    int blackMark=getScore(mapBlack);
    int whiteMark=getScore(mapWhite);
    if(C_BLACK==col&&blackMark>=M_lose){
        return S_WIN;
        //胜利
    }
    if(C_WHITE==col&&whiteMark>=M_WIN){
        return S_LOSE;
        //失败
    }
    return S_WAIT;
    //未决
}

void Evaluator::setNeeds(int i, int j)
{
    //周围5x5的区域变成可选域
    for(int bi=i-2;bi<=i+2;++bi){
        for(int bj=j-2;bj<=j+2;++bj){
            if(isValid(bi,bj))need[bi][bj]=true;
        }
    }
}
void Evaluator::restart()
{
    memset(need,0,sizeof need);
}

//由于循环引用的原因，这里的某些inline函数无法放进头文件
//考虑到实际上只有evaluator.cpp存在对这些函数的调用，故定义写在cpp文件中依然能够保持inline的性质
//所以索性全部在这里了
inline bool Evaluator::isValid(int i,int j){
    return (i>=0&&i<NUMBER)&&(j>=0&&j<NUMBER);
}
inline bool Evaluator::isNeed(int i, int j)
{
    return need[i][j];
}

inline int &Evaluator::getEle(int i, int j)
{
    return parent->chess[i][j];
}
inline int Evaluator::getEle(int i, int j)const
{
    return parent->chess[i][j];
}

#include "evaluator.h"
#include "def.h"
#include"utility.h"
#include<QMessageBox>
#include"widget.h"
#include"ui_widget.h"

Evaluator::Evaluator(Widget *parent)
{
    this->parent=parent;
    init();
}
void Evaluator::init()
{
    initMap();
    memset(need, 0, sizeof need);
}
int Evaluator::greedy(int color){
    int bmark=color==C_BLACK?INT_MAX:INT_MIN;
    int mark=-1,markBlack,markWhite;

    for(int i=0;i<NUMBER;++i){
        for(int j=0;j<NUMBER;++j){
            if(isNeed(i,j)&&C_EMPTY==parent->chess[i][j]){
                getEle(i,j)=color;

                markWhite=eval(mapWhite);
                markBlack=eval(mapBlack);
                mark=markWhite-markBlack;

                if(markWhite>=M_WIN&&markBlack<M_lose)mark=INT_MAX;
                else if(markWhite<M_WIN&&markBlack>=M_lose)mark=INT_MIN;

                parent->chess[i][j]=C_EMPTY;
                bmark=color==C_BLACK?min(bmark,mark):max(bmark,mark);
            }
        }
    }
    return bmark;
}

inline bool Evaluator::isNeed(int i, int j)
{
    return need[i][j];
}

inline int &Evaluator::getEle(int i, int j)
{
    return parent->chess[i][j];
}
int Evaluator::max_min_search(int col, int alpha, int beta, int depth){
    if(MAX_LEVEL==depth)
        return greedy(C_BLACK);
    int bmark,mark;
    bmark=depth&1?INT_MIN:INT_MAX;
    if (alpha>=beta)return bmark;
    NBig Q;getNBig(Q,depth,col);
    while(Q.size()){
        if(alpha>=beta)return bmark;
        const Node &temp=Q.pop();
        getEle(temp.row,temp.col)=col;
        mark=max_min_search(C_BLACK+C_WHITE-col,alpha,beta,depth+1);
        getEle(temp.row,temp.col)=C_EMPTY;
        if(depth&1){
            bmark=max(bmark,mark);
            alpha=max(alpha, mark);
        }
        else{
            bmark=min(bmark,mark);
            beta=min(beta,mark);
        }
        if(alpha>=beta)return bmark;
    }
    return bmark;
}
void Evaluator::getNBig(NBig& Q,int depth,int col){
    for(int i=0;i<NUMBER;++i){
        for(int j=0;j<NUMBER;++j){
            //贪心，寻找候选人

            if(isNeed(i,j)&&C_EMPTY==getEle(i,j)){
                getEle(i,j)=col;

//                int mark=greedy(C_BLACK+C_WHITE-col);

                int markWhite=eval(mapWhite);
                int markBlack=eval(mapBlack);
                int mark=markWhite-markBlack;

                //一步必胜或者必败
                if(depth&1){
                    if(markBlack>=M_lose&&markWhite<M_WIN)mark=INT_MIN;
                    else if(markBlack<M_lose&&markWhite>=M_WIN)mark=INT_MAX;
                }
                else{
                    //human
                    if(markBlack<M_lose&&markWhite>=M_WIN)mark=INT_MAX;
                    else if(markBlack>=M_lose&&markWhite<M_WIN)mark=INT_MIN;
                }

                getEle(i,j)=C_EMPTY;
                //估值完毕后应该迅速改回颜色
                //这里的mark是贪心出来的结果（考虑了使用胜利和失败判定去稍微优化它）
                if(depth&1)Q.push(Node(mark,i,j));
                else Q.push(Node(-1*mark,i,j));
                //abs(INT_MAX)<abs(INT_MIN)所以不用考虑溢出
            }

        }
    }
}
int Evaluator::eval(const map<string,int> &mp)
{
    //column
    int mark=0;
    string temp;
    temp.reserve(unsigned(NUMBER+3));
    for(int i=0;i<NUMBER;++i){
        for(int j=0;j<NUMBER;++j){
            if(0==j)temp="3";
            temp+=int2char(getEle(i,j));
            if((NUMBER-1)==j)temp+="3";
        }
        match(mark,temp,mp);
    }
    //rows
    for(int i=0;i<NUMBER;++i){
        for(int j=0;j<NUMBER;++j){
            if(0==j)temp="3";
            temp+=int2char(getEle(j,i));
            if((NUMBER-1)==j)temp+="3";
        }
        match(mark,temp,mp);
    }

    {
        //主对角线
        for(int i=0;i<NUMBER;++i){
            if(0==i)temp="3";
            temp+=int2char(getEle(i,i));
            if(NUMBER-1==i)temp+="3";

        }
        match(mark,temp,mp);
    }
    //主上三角
    for(int k=1;k<NUMBER;++k){
        for(int i=0,j=k;j<NUMBER;++i,++j){
            if(0==i)temp="3";
            temp+=int2char(getEle(i,j));
            if(NUMBER-1==j)temp+="3";
        }
        match(mark,temp,mp);
    }
    //主下三角
    for(int k=1;k<NUMBER;++k){
        for(int i=0,j=k;j<NUMBER;++i,++j){
            if(0==i)temp="3";
            temp+=int2char(getEle(j,i));
            if(NUMBER-1==j)temp+="3";
        }
        match(mark,temp,mp);
    }


    {
        //次对角线
        for(int i=0;i<NUMBER;++i){
            if(0==i)temp="3";
            temp+=int2char(getEle(i,NUMBER-1-i));
            if(NUMBER-1==i)temp+="3";

        }
        match(mark,temp,mp);
    }
    //次上三角
    for(int k=0;k<NUMBER-1;++k){
        for(int i=0;i<=k;++i){
            if(0==i)temp="3";
            temp+=int2char(getEle(i,k-i));
            if(0==k-i)temp+="3";
        }
        match(mark,temp,mp);
    }
    //次下三角
    for(int k=NUMBER;k<=2*NUMBER-2;++k){
        for(int j=NUMBER-1;(k-j)<NUMBER;--j){
            if(NUMBER-1==j)temp="3";
            temp+=int2char(getEle(k-j,j));
            if(NUMBER-1==k-j)temp+="3";
        }
        match(mark,temp,mp);
    }
    return mark;
}

void Evaluator::match(int &sum, string &temp,const map<string,int> &mp)
{
    if(&mp==&mapWhite){
        if(memWhite.count(temp)){
            sum+=memWhite[temp];
            return;
        }
    }
    else{
        if(memBlack.count(temp)){
            sum+=memBlack[temp];
            return;
        }
    }
    unsigned long long index;
    int add=0;
    for(auto itr=mp.begin();itr!=mp.end();++itr){
        index=0;
        while(  (index=temp.find(itr->first,index))<temp.length()  ){
            ++index;
            sum+=itr->second;
            add+=itr->second;
        }
    }
    if(&mp==&mapWhite){
        memWhite[temp]=add;
    }
    else{
        memBlack[temp]=add;
    }
}
int Evaluator::checkTie()const
{
    if(parent->counter==NUMBER*NUMBER)return S_TIE;
    else return S_WAIT;
}

int Evaluator::check(int col)
{
    int blackMark,whiteMark;
    if(checkTie()==S_TIE)return S_TIE;
    blackMark=eval(mapBlack);
    whiteMark=eval(mapWhite);
    if(C_BLACK==col&&blackMark>=M_lose){
        return S_WIN;
    }
    if(C_WHITE==col&&whiteMark>=M_WIN){
        return S_LOSE;
    }
    return S_WAIT;
}

void Evaluator::setNeeds(int i, int j)
{
    for(int bi=i-2;bi<=i+2;++bi){
        for(int bj=j-2;bj<=j+2;++bj){
            if(isValid(bi,bj))need[bi][bj]=true;
        }
    }
}
inline bool Evaluator::isValid(int i,int j){
    return (i>=0&&i<NUMBER)&&(j>=0&&j<NUMBER);
}

#ifndef EVALUATOR_H
#define EVALUATOR_H
#include"utility.h"

class GoBang;
//GoBang是棋盘界面类，这里把棋盘的UI和AI部分分离
//用类前向声明和指针对付循环引用咯。
class Evaluator //AI类
{
private:
    GoBang* parent; //某种意义上的父吧
    int need[NUMBER][NUMBER];

    map<string,int> mapWhite, mapBlack;
    //棋形映射为字符串，字符串映射为分值
    //由于棋形匹配需要进行遍历，故使用map效率较高

    mutable unordered_map<string,int> memWhite, memBlack;
    //这个是记忆化字典
    //由于记忆化需要频繁查找，使用hash效率较高
public:
    Evaluator(GoBang* parent);
    void restart();
	void init();
    void initMap();
    void initWeight();
    void initMapWhite();
    void initMapBlack();
    void initMap(int level, string str, bool isBlock, bool isBlack);
    //递归地构造棋形

    int max_min_search(int col, int alpha, int beta, int depth);//极大极小搜索算法
    int greedy_search(int color);  //贪心搜索算法，一般在博弈树的最后一层
    void getNBig(NBig& Q,int depth,int col);    //用于获得每层的N个合理下法

    int getScore(const map<string,int> &mp)const;   //分别对黑白棋，对整个棋面评分
    int matchString(string &str,const map<string,int> &mp)const;    //分别对黑白棋，对一条线进行评分

    int check(int col) const;   //检测棋局状态
    bool checkTie()const;

    inline bool isValid(int i,int j);
    void setNeeds(int i,int j);
    inline bool isNeed(int i,int j);
    //isNeed可以使得我们搜索只搜索周围的棋子，减少搜索范围

    inline int& getEle(int i,int j);
    inline int getEle(int i,int j)const;
};

#endif // EVALUATOR_H

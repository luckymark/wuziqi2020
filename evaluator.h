#ifndef EVALUATOR_H
#define EVALUATOR_H

#include"utility.h"
class Widget;
//用前向声明和指针对付循环引用咯。
class Evaluator
{
private:
    Widget* parent;
    int need[15][15];
    map<string, int> mapWhite, mapBlack;
    unordered_map<string, int> memWhite, memBlack;
public:
    Evaluator(Widget* parent);
	void init();
    void initWeight();
    void initMap();
    void initMapWhite();
    void initMapBlack();
    void initMap(int level, string str, bool isBlock, bool isBlack);


    int greedy(int color);
    int max_min_search(int col, int alpha, int beta, int depth);
    void match(int &sum, string &temp,const map<string,int> &mp);
    int eval(const map<string,int> &mp);
    void getNBig(NBig& Q,int depth,int col);

    int checkTie()const;
    int check(int col);

    inline bool isValid(int i,int j);
    void setNeeds(int i,int j);
    inline bool isNeed(int i,int j);
    inline int& getEle(int i,int j);
};

#endif // EVALUATOR_H

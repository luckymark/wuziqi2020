#ifndef BIGN_H
#define BIGN_H
#include<algorithm>
#include<queue>
struct Node{
    //This class is used by NBig
    int mark;   //分值
    int row;    //行号
    int col;    //列号
    Node(int _mark,int _row,int _col):
        mark(_mark),row(_row),col(_col)
    {
    }
    Node()=default;
    bool operator<(const Node &i)const{
        return mark<i.mark;
    }
    //重载小于号便于按照分值排序
};


struct NBig{
    //UPD: 更改最初栈的实现方式为有限长度优先队列
    //有限长度是为了减少不必要的中间节点，即减少每层搜索数目
    //优先队列FIFO相比栈的FILO的好处在于贪心最优的点最先被搜索，有利于alpha-beta剪枝
    //实测常数减少为0.5~0.8


    //经过一些测试得出，在和大佬下的时候，实际上合理的走法是很少的
    //保留前N个较大的数，这是为了减少不合理的中间节点
#define N 3
    //经过测试，3看上去足够了
    NBig():_beg(0),_end(0)
    {
        //NBig是一个容器
    }
    int size()const {
        return _end-_beg;
    }
    void push(const Node& x){
        //偷懒使用优先队列来维护单调性，虽然这样实现看上去效率不高，但是占总体开销很小可以忽略。
        std::priority_queue<Node> Q;
        for(int i=0;i<_end;++i)Q.push(arr[i]);
        Q.push(x);
        //把原有的元素和新元素放入优先队列
        _end=0;
        while(!Q.empty()&&_end<N){
            arr[_end++]=Q.top();
            Q.pop();
        }
        //从优先队列中取出元素
    }
    const Node& pop(){
        return arr[_beg++];
    }
    void clear(){
        _beg=_end=0;
    }
private:
    Node arr[N];
    int _end;
    int _beg;
#undef N
};
#endif // BIGN_H

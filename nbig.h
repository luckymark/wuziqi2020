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
    //经过一些测试得出，在和大佬下的时候，实际上合理的走法是很少的
    //保留前N个较大的数，这是为了减少不合理的中间节点
#define N 3
    //经过测试，3看上去足够了
    NBig():_size(0)
    {
        //NBig是一个容器
    }
    int size()const {
        return _size;
    }
    void push(const Node& x){
        //偷懒使用优先队列来维护单调性，虽然这样实现看上去效率不高，但是占总体开销很小可以忽略。
        std::priority_queue<Node> Q;
        for(int i=0;i<_size;++i)Q.push(arr[i]);
        Q.push(x);
        //把原有的元素和新元素放入优先队列
        _size=0;
        while(!Q.empty()&&_size<N){
            arr[_size++]=Q.top();
            Q.pop();
        }
        //从优先队列中取出元素
    }
    const Node& pop(){
        return arr[--_size];
    }
    void clear(){
        _size=0;
    }
private:
    Node arr[N];
    int _size;
#undef N
};
#endif // BIGN_H

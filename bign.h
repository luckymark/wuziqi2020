#ifndef BIGN_H
#define BIGN_H
#include<algorithm>
#include<queue>
struct Node{
    int mark;
    int row;
    int col;
    Node(int _mark,int _row,int _col):
        mark(_mark),row(_row),col(_col)
    {
    }
    Node()=default;
    bool operator<(const Node &i)const{
        return mark<i.mark;
    }
};


struct NBig{
    //保留前N个较大的数，这是为了减少无意义的中间节点
    //经过一些测试得出，在和大佬下的时候，实际上合理的走法是很少的
#define N 3
    NBig():_size(0)
    {

    }
    int size()const {
        return _size;
    }

    void push(const Node& x){
        std::priority_queue<Node> Q;
        for(int i=0;i<_size;++i)Q.push(arr[i]);
        _size=0;
        Q.push(x);
        while(!Q.empty()&&_size<N){
            arr[_size++]=Q.top();
            Q.pop();
        }
    }

    const Node& pop(){
        return arr[--_size];
    }
private:
    Node arr[N];
    int _size;
#undef N
};

#endif // BIGN_H
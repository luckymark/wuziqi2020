//
// Created by 20694 on 2020/5/10.
//
#include "state.h"

extern int board[row][col];
extern int is_empty[row][col];

dir da={1,0};
dir db={0,1};
dir dc={1,1};
dir dd={-1,1};
//评估棋型
bool is_in_board(int x,int y){
    return !(x > 15 || y > 15 || x < 1 || y  < 1);
}
dir next_point(dir p,dir d,int des){
    dir p_;
    p_.x=p.x+des*d.x;
    p_.y=p.y+des*d.y;
    return p_;
}
int state_score(int x,int y,int color){
    int d;int left[5];int right[5];int w5,a4,a3,a2,a1,d4,d3,d2,d1,cnt,l;
    w5=a4=a3=a2=a1=d4=d3=d2=d1=cnt=l=0;
    dir Dir,point,point_;
    point.x=x;point.y=y;
    Dir.x=Dir.y=0;
    for(d=1;d<=4;d++){
        switch (d){
            case 1: Dir=da;
                break;
            case 2: Dir=db;
                break;
            case 3: Dir=dc;
                break;
            case 4: Dir=dd;
                break;
            default:break;
        }
        point_=next_point(point,Dir,1);
        while(is_in_board(point_.x,point_.y)&&board[point_.x][point_.y]){
            l++;
            next_point(point,Dir,1);
        }
        point_=next_point(point,Dir,-1);
        while(is_in_board(point_.x,point_.y)&&board[point_.x][point_.y]){
            l++;
            next_point(point,Dir,-1);
        }
    }

}



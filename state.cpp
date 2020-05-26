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
int get_color_(int color) {
    int color_;
    if(white == color){
        color_=black;
    }else{
        color_=white;
    }
    return color_;
}
dir next_point(dir p,dir d,int des){
    dir p_;
    p_.x=p.x+des*d.x;
    p_.y=p.y+des*d.y;
    return p_;
}
int state_score(int x,int y,int color){
    int left[5]={0};int right[5]={0};int d,cnt,l,color_,score;
    color_=get_color_(color);
    score=cnt=0;
    dir Dir,point,point_,le,ri;
    point.x=x;point.y=y;
    Dir.x=Dir.y=ri.x=ri.y=le.x=le.y=0;
    for(d=1;d<=4;d++){
        l=1;
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
        while(is_in_board(point_.x,point_.y)&&board[point_.x][point_.y]==color){
            l++;
            ri=point_;
            point_=next_point(point_,Dir,1);
        }
        point_=next_point(point,Dir,-1);
        while(is_in_board(point_.x,point_.y)&&board[point_.x][point_.y]==color){
            l++;
            le=point_;
            point_=next_point(point_,Dir,-1);
        }
        for(cnt=1;cnt<=4;cnt++){
            point_=next_point(ri,Dir,cnt);
            if(is_in_board(point_.x,point_.y)){
                right[cnt]=board[point_.x][point_.y];
            }else{
                right[cnt]=color_;
            }
            point_=next_point(le,Dir,-cnt);
            if(is_in_board(point_.x,point_.y)){
                right[cnt]=board[point_.x][point_.y];
            }else{
                right[cnt]=color_;
            }
        }
        while(true){
            if(win5(left,right,l,color)){
                score+=win5(left,right,l,color);
                break;
            }
            if(alive4(left,right,l,color)){
                score+=alive4(left,right,l,color);
                break;
            }
            if(dead4(left,right,l,color)){
                score+=dead4(left,right,l,color);
                break;
            }
            if(alive3(left,right,l,color)){
                score+=alive3(left,right,l,color);
                break;
            }
            if(dead3(left,right,l,color)){
                score+=dead3(left,right,l,color);
                break;
            }
            if(alive2(left,right,l,color)){
                score+=alive2(left,right,l,color);
                break;
            }
            if(dead2(left,right,l,color)){
                score+=dead2(left,right,l,color);
                break;
            }
            else break;
        }
    }
    return score;
}



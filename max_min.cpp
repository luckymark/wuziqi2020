//
// Created by 20694 on 2020/5/26.
//
#include "max_min.h"

extern int board[col][row];
extern int player;
extern point best;

int Max(int x, int y){
    if(x>y){return x;}
    else return y;
}

void initialization(point*p0){
    for(int i=0;i<square;i++){
        p0[i].x=p0[i].y=p0[i].score=0;
    }
}

int Min(int x,int y){
    if(x>y){return y;}
    else return x;
}

int find_point(point*p){
    int cnt=0;
    initialization(p);
    for(int i=1;i<col;i++)
        for(int j=1;j<row;j++)
        {
            if(board[i][j]==empty){
                p[cnt].x=i;
                p[cnt].y=j;
                cnt++;
            }
        }
    return cnt;
}

int max_min(int deep,int color) {
    int alpha=min,beta=max;
    point p[square];
    stack best_nodes;
    init(&best_nodes);
    int color_, length, score, pawn_score;
    pawn_score = score = length = 0;
    length = find_point(p);
    if (length == 0) { exit(0); }
    color_ = get_color_(color);
    if(color!=player) {pawn_score = min;}
    else {pawn_score=max;}
    for (int i = 0; i < length; i++) {
        board[p[i].x][p[i].y] = color;
        if(color!=player){
            if(deep==1){score=state_score(p[i].x,p[i].y,color);}
            else score=max_min(deep-1,color_);
            if(score>beta) {
                board[p[i].x][p[i].y] = empty;
                return max;
            }
        }else{
            if(deep==1){score=-state_score(p[i].x,p[i].y,color);}
            else score=max_min(deep-1,color_);
            if(score<alpha) {
                board[p[i].x][p[i].y] = empty;
                return min;
            }
        }
        p[i].score = score;
        pop_stack(i, best_nodes, pawn_score, p, color);
        board[p[i].x][p[i].y] = empty;
        }
        if (!is_empty(&best_nodes)) {
            point pr;
            pr = top(&best_nodes);
            best = pr;
            if(color==player){alpha=pr.score;}
            else{beta=pr.score;}
            return pr.score;
        }
        if (deep == 4) { best = top(&best_nodes); }
        return pawn_score;
}
//
// Created by 20694 on 2020/5/26.
//
#include "max_min.h"

extern int board[col][row];
extern int player;
extern point best;

int exam(){
    int EXAM=0;
    point exam[square];
    point pe[square];
    exam[0].x=1;
    stack s;
    init(&s);
    exam[0]=top(&s);
    if(exam[0].x!=0&&exam[0].y!=0&&exam[0].score!=0) return 0;
    int pawn_score=100;
    exam[1].score=20;
    pop_stack(1,s,pawn_score,exam,black);
    return is_empty(&s);
}

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
        if(deep==1){
            if(color!=player){
                score=state_score(p[i].x,p[i].y,color);
            }else{
                score=-state_score(p[i].x,p[i].y,color);
            }
        }else {score = max_min(deep - 1, color_);}
        p[i].score = score;
        pop_stack(i, best_nodes, pawn_score, p, color);
        board[p[i].x][p[i].y] = empty;
        }
        if (!is_empty(&best_nodes)) {
            point pr;
            pr = top(&best_nodes);
            best = pr;
            return pr.score;
        } else assert(0);
        if (deep == 4) { best = top(&best_nodes); }
        return pawn_score;
}
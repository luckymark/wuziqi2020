//
// Created by 20694 on 2020/6/13.
//
#include "stack.h"

extern int player;

void push(stack*s,point p0){
    s->p[s->top].x=p0.x;
    s->p[s->top].y=p0.y;
    s->p[s->top].score=p0.score;
    s->top++;
}

point top(stack*s){
    s->top--;
    return s->p[s->top];
}

bool is_empty(stack*s){
    return s->top==0;
}

void pop(stack*s){
    s->top--;
}

void init(stack*s){
    s->top=0;
    initialization(s->p);
}

void pop_stack(int i, stack &best_nodes, int &pawn_score,point*p,int color) {
    if(color!=player) {
        if (pawn_score < p[i].score) {
            if (is_empty(&best_nodes)) {
                push(&best_nodes, p[i]);
            } else {
                while (!is_empty(&best_nodes)) {
                    pop(&best_nodes);
                }
                push(&best_nodes, p[i]);
            }
            pawn_score = p[i].score;
        }
    }
    if(color==player){
        if (pawn_score > p[i].score) {
            if (is_empty(&best_nodes)) {
                push(&best_nodes, p[i]);
            } else {
                while (!is_empty(&best_nodes)) {
                    pop(&best_nodes);
                }
                push(&best_nodes, p[i]);
            }
            pawn_score = p[i].score;
        }
    }
}
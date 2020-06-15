//
// Created by 20694 on 2020/6/13.
//

#ifndef GOBANG_STACK_H
#define GOBANG_STACK_H

#include "main.h"

typedef struct STACK{
    point p[square];
    int top;
    int cap;
}stack;

void push(stack*s,point p0);
void pop(stack*s);
void init(stack*s);
bool is_empty(stack*s);
point top(stack*s);
void pop_stack(int i, stack &best_nodes, int &pawn_score,point*p,int color);

#endif //GOBANG_STACK_H

//
// Created by 20694 on 2020/5/10.
//

#ifndef GOBANG_STATE_H
#define GOBANG_STATE_H

#include "main.h"
#include "pawn_score.h"

typedef struct Dir{
    int x;
    int y;
}dir;

bool is_in_board(int x,int y);
dir next_point(dir p,dir d,int des);

#endif //GOBANG_STATE_H

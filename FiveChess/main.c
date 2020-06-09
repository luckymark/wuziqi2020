/**
 * @author Artificial01
 * @date 2020-6-9
 * @version 2.0
 * */

/* 这个项目主要三篇代码：main.c 、 AI.h 、 Board.h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <synchapi.h>
#include <locale.h>

#include "AI.h"
#include "Board.h"

int main() {
    initBoard();
    for(;;){
        drawBoard();
        ifWin();
        turnSwitch();
        placeChess();
        system("cls");
    }
}

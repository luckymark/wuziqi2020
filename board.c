#include "board.h"
#include <stdio.h>
#include <string.h>

#define FG_RGB FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN
#define BG_RGB BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN

#define PRINTLINE(L, M, R) do {\
    if (j == 0)              dprint(h, L);\
    else if (j == MAX_Y - 1) dprint(h, R);\
    else                     dprint(h, M);\
} while(0)

void dprint(HANDLE h, char dchar[]) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(h, &info);
	printf("%s", dchar);
    COORD position = { info.dwCursorPosition.X + 2, info.dwCursorPosition.Y };
	SetConsoleCursorPosition(h, position);
}

void clearscreen() {
    for (int i = 0; i < MAX_X + 2; i++) {
        for (int j = 0; j < MAX_Y * 2 + 4; j++) {
            putchar(' ');
        }
        putchar('\n');
    }
}

void paintbox(HANDLE h) {
    COORD position = { 0, 0 };
    SetConsoleCursorPosition(h, position);
    for (int i = 0; i < MAX_X; i++) {
        printf("\n  ");
        for (int j = 0; j < MAX_Y; j++) {
            if (i == 0)              PRINTLINE("┏", "┯", "┓");
            else if (i == MAX_X - 1) PRINTLINE("┗", "┷", "┛");
            else                     PRINTLINE("┠", "┼", "┨");
        }
    }
}

void setboard(HANDLE h, Board *board) {
    // initialize the board
    memset((*board).a, NONE, sizeof((*board).a));
    // hide cursor
    CONSOLE_CURSOR_INFO info = {1, 0};
    SetConsoleCursorInfo(h, &info);
    // set window size
    SMALL_RECT rect;
    rect.Top = rect.Left = 0;
    rect.Bottom = MAX_X + 1, rect.Right = MAX_Y * 2 + 3;
    SetConsoleWindowInfo(h, TRUE, &rect);
    // set text & backgroud color
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY|BG_RGB);
    // praint board
    clearscreen();
    paintbox(h);
}

void putchess(HANDLE h, Board *board, int x, int y, chess c) {
    if ((*board).a[x][y] == NONE) {
        (*board).a[x][y] = c;
        COORD position = { y * 2 + 2, x + 1 };
        SetConsoleCursorPosition(h, position);
        SetConsoleTextAttribute(h, (c == BLACK ? 0 : FOREGROUND_INTENSITY|FG_RGB)|BG_RGB);
        dprint(h, "●");
    }
}
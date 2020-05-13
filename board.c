#include "board.h"
#include <stdio.h>
#include <string.h>

#define FG_RGB FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE
#define BG_RGB BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE

#define PRINTLINE(L, M, R) do {\
    if (j == 0)              dprint(h, L);\
    else if (j == MAX_Y - 1) dprint(h, R);\
    else                     dprint(h, M);\
} while(0)

#define GO(h, x, y) do {\
    COORD position = { x, y };\
    SetConsoleCursorPosition(h, position);\
} while(0)

static void dprint(HANDLE h, char dchar[]) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(h, &info);
    printf("%s", dchar);
    GO(h, info.dwCursorPosition.X + 2, info.dwCursorPosition.Y);
}

static void clearscreen(HANDLE h) {
    GO(h, 0, 0);
    for (int i = 0; i < MAX_X + 2; i++) {
        for (int j = 0; j < MAX_Y * 2 + 4; j++) {
            putchar(' ');
        }
        putchar('\n');
    }
}

static void paintbox(HANDLE h) {
    GO(h, 0, 0);
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
    SetConsoleTitle("右键属性取消快速编辑");
    // initialize the board array
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
    // paint board
    clearscreen(h);
    paintbox(h);
}

void putchess(HANDLE h, Board *board, int x, int y, chess c) {
    if ((*board).a[x][y] == NONE) {
        (*board).a[x][y] = c;
        GO(h, y * 2 + 2, x + 1);
        SetConsoleTextAttribute(h, (c == BLACK ? 0 : FOREGROUND_INTENSITY|FG_RGB)|BG_RGB);
        dprint(h, "●");
    }
}
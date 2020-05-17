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

#define COMPARE(board, x, y, c) (0 <= x && x < MAX_X && 0 <= y && y < MAX_Y && (*board).a[x][y] == c)

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
    memset((*board).a, NONE, sizeof((*board).a));               // 棋盘清零
    CONSOLE_CURSOR_INFO info = {1, 0};
    SetConsoleCursorInfo(h, &info);                             // 隐藏光标
    SMALL_RECT rect;
    rect.Top = rect.Left = 0;
    rect.Bottom = MAX_X + 1, rect.Right = MAX_Y * 2 + 3;
    SetConsoleWindowInfo(h, TRUE, &rect);                       // 调整窗口
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY|BG_RGB);    // 设置颜色
    clearscreen(h);                                             // 清除屏幕
    paintbox(h);                                                // 绘制棋盘
}

status putchess(HANDLE h, Board *board, int x, int y, chess c) {
    if (COMPARE(board, x, y, NONE)) {
        (*board).a[x][y] = c;
        GO(h, y * 2 + 2, x + 1);
        SetConsoleTextAttribute(h, (c == BLACK ? 0 : FOREGROUND_INTENSITY|FG_RGB)|BG_RGB);
        dprint(h, "●");
        const int dxy[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };
        for (int k = 0; k < 4; k++) {
            int continued = 0;
            for (int i = x, j = y; COMPARE(board, i, j, c); i += dxy[k][0], j += dxy[k][1])
                continued++;
            for (int i = x, j = y; COMPARE(board, i, j, c); i -= dxy[k][0], j -= dxy[k][1])
                continued++;
            if (continued > 5)
                return GAMEOVER;
        }
        return AVAILABLE;
    }
    return OCCUPIED;
}
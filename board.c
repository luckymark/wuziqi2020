#include "board.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

#define FG_RGB FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE
#define BG_RGB BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE

#define PRINTLINE(L, M, R) do {\
    if (j == 0)              dprint(h, L);\
    else if (j == MAX_Y - 1) dprint(h, R);\
    else                     dprint(h, M);\
} while (0)

#define CLEARCHESS(L, M, R) do {\
    switch (tryY + 1) {\
        case     1: dprint(h, L); break;\
        default   : dprint(h, M); break;\
        case MAX_Y: dprint(h, R); break;\
    }\
} while (0)

#define GO(h, x, y) do {\
    COORD position = { x, y };\
    SetConsoleCursorPosition(h, position);\
} while (0)

#define COMPARE(board, x, y, c) (0 <= x && x < MAX_X && 0 <= y && y < MAX_Y && (*board).a[x][y] == c)

static int tryX, tryY;
static const WORD colors[3] = {
    FOREGROUND_INTENSITY|BG_RGB,
    BG_RGB,
    FOREGROUND_INTENSITY|FG_RGB|BG_RGB
};

static void dprint(HANDLE h, char dchar[]);
static void clearscreen(HANDLE h);
static void paintbox(HANDLE h);

static void dprint(HANDLE h, char dchar[]) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(h, &info);
    printf("%s", dchar);
    GO(h, info.dwCursorPosition.X + 2, info.dwCursorPosition.Y);
}

static void clearscreen(HANDLE h) {
    for (int i = 0; i < MAX_X + 2; i++) {
        GO(h, 0, i);
        for (int j = 0; j < MAX_Y * 2 + 4; j++) {
            putchar(' ');
        }
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
    SetConsoleWindowInfo(h, TRUE, &rect);                       // 缩放窗口
    SetConsoleTextAttribute(h, colors[NONE]);                   // 设置颜色
    clearscreen(h);                                             // 清空屏幕
    paintbox(h);                                                // 绘制棋盘
    if (LOG) {
        struct tm* tblock;
        time_t timer = time(NULL);
        tblock = localtime(&timer);
        FILE *fp = fopen(FILENAME, "a");
        fprintf(fp, "\n\n%s", asctime(tblock));
    }
}

status putchess(HANDLE h, Board *board, int x, int y, chess c) {
    if ((*board).a[tryX][tryY] == NONE) {
        SetConsoleTextAttribute(h, colors[NONE]);
        GO(h, tryY * 2 + 2, tryX + 1); printf("  ");
        GO(h, tryY * 2 + 2, tryX + 1);
        switch (tryX + 1) {
            case     1: CLEARCHESS("┏", "┯", "┓"); break;
            default   : CLEARCHESS("┠", "┼", "┨"); break;
            case MAX_X: CLEARCHESS("┗", "┷", "┛"); break;
        }
    }
    if (COMPARE(board, x, y, NONE)) {
        GO(h, y * 2 + 2, x + 1);
        SetConsoleTextAttribute(h, colors[c]);
        dprint(h, "●");
        if (c == NONE) {
            tryX = x, tryY = y;
        }
        else {
            if (LOG) {
                FILE *fp = fopen(FILENAME, "a");
                fprintf(fp, "{%d,%d,%d},", x, y, c);
            }
            (*board).a[x][y] = c;
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
        }
        return AVAILABLE;
    }
    return OCCUPIED;
}
#define TEST 0 // 0=off 1=on
#include "board.h"
#include "brain.h"

HANDLE hOUT, hIN;
Board board;
Lines lines;

void test();
void init();
void gameover(chess winner);
DWORD click(COORD *position);

int main() {
    init();
    while (1) {
        COORD position;
        if (click(&position) == FROM_LEFT_1ST_BUTTON_PRESSED) {
            switch (putchess(hOUT, &board, position.X, position.Y, BLACK)) {
            case AVAILABLE:
                putchess_lines(&lines, position.X, position.Y, BLACK);

                SetConsoleTitle("轮到我白子，你等会儿");
                MinimaxInfo info = minimax(&lines, 1, 0, -oo, +oo);
                if (info.x == -1)
                    gameover(NONE);
                else {
                    putchess_lines(&lines, info.x, info.y, WHITE);
                    if (putchess(hOUT, &board, info.x, info.y, WHITE) == GAMEOVER)
                        gameover(WHITE);
                    else
                        SetConsoleTitle("现在轮到你的黑子下了");
                }
                break;
            case GAMEOVER:
                gameover(BLACK);
                break;
            default: break;
            }
        }
        else {
            putchess(hOUT, &board, position.X, position.Y, NONE);
        }
    }
    return 0;
}

void test() {
    int chesses[][3] = {
        {5,7,2},
        {6,6,2},{6,8,2},{6,9,2},
        {7,5,2},{7,6,2},{7,7,1},{7,8,1},{7,9,1},{7,10,2},
        {8,4,1},{8,6,1},{8,7,1},{8,8,2},{8,9,1},
        {9,3,2},{9,4,1},{9,5,1},{9,6,1},{9,7,1},{9,8,2},
        {10,5,2},{10,7,2},{10,8,1}
    };
    for (int k = 0; k < 24; k++) {
        putchess(hOUT, &board, chesses[k][0], chesses[k][1], chesses[k][2]);
        putchess_lines(&lines, chesses[k][0], chesses[k][1], chesses[k][2]);
    }
}

void init() {
    hOUT = GetStdHandle(STD_OUTPUT_HANDLE);
    hIN  = GetStdHandle(STD_INPUT_HANDLE);
    setboard(hOUT, &board);
    SetConsoleTitle("等等！偷看棋谱中……");
    preprocess();
    ////////////////////
    if (TEST)
        test();
    ////////////////////
    SetConsoleTitle("右键属性取消快速编辑");
}

void gameover(chess winner) {
    if (winner == NONE)
        SetConsoleTitle("啊，这……，右键重开");
    if (winner == BLACK)
        SetConsoleTitle("赢，黑子胜，右键重开");
    if (winner == WHITE)
        SetConsoleTitle("输，白子胜，右键重开");

    COORD position;
    while (click(&position) != RIGHTMOST_BUTTON_PRESSED);

    setboard(hOUT, &board);
    init_lines(&lines);
    ////////////////////
    if (TEST)
        test();
    ////////////////////
    SetConsoleTitle("黑子先手，你先来，请");
}

DWORD click(COORD *position) {
    DWORD number;
    INPUT_RECORD buffer;
    FlushConsoleInputBuffer(hIN);
    ReadConsoleInput(hIN, &buffer, 1, &number);

    if (buffer.EventType == MOUSE_EVENT) {
        (*position) = buffer.Event.MouseEvent.dwMousePosition;
        int tempX = (*position).X;
        (*position).X = (*position).Y - 1;
        (*position).Y = (tempX - 2) / 2;
        return buffer.Event.MouseEvent.dwButtonState;
    }
    else
        return 0;
}
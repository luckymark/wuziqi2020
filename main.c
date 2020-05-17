#include "board.h"
#include "brain.h"

HANDLE hOUT, hIN;
Board board;
Lines lines;

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
                    putchess_lines(&lines, info.x, info.y, WHITE);
                    if (putchess(hOUT, &board, info.x, info.y, WHITE) == GAMEOVER)
                        gameover(WHITE);
                    else
                        SetConsoleTitle("现在轮到你的黑子下了");
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

void init() {
    hOUT = GetStdHandle(STD_OUTPUT_HANDLE);
    hIN  = GetStdHandle(STD_INPUT_HANDLE);
    setboard(hOUT, &board);
    SetConsoleTitle("等等！偷看棋谱中……");
    preprocess();
    SetConsoleTitle("右键属性取消快速编辑");
}

void gameover(chess winner) {
    if (winner == BLACK)
        SetConsoleTitle("赢，黑子胜，右键重开");
    if (winner == WHITE)
        SetConsoleTitle("输，白子胜，右键重开");

    COORD position;
    while (click(&position) != RIGHTMOST_BUTTON_PRESSED);
    
    setboard(hOUT, &board);
    init_lines(&lines);
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
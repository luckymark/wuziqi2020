#include "board.h"
#include "brain.h"

HANDLE hOUT, hIN;
Board board;
Lines lines;

void init();
DWORD click(COORD *position);

int main() {
    init();
    while (1) {
        COORD position;
        FlushConsoleInputBuffer(hIN);
        if (click(&position) == FROM_LEFT_1ST_BUTTON_PRESSED) {
            int x = position.Y - 1;
            int y = (position.X - 2) / 2;
            switch (putchess(hOUT, &board, x, y, BLACK)) {
                case AVAILABLE:
                    SetConsoleTitle("轮到我白子，你等会儿");
                    putchess_lines(&lines, x, y, BLACK);
                    MinimaxInfo info = minimax(&lines, 1, 0, -oo, +oo);
                    putchess_lines(&lines, info.x, info.y, WHITE);
                    if (putchess(hOUT, &board, info.x, info.y, WHITE) == GAMEOVER) {
                        SetConsoleTitle("输，白子胜，右键重开");
                        while (click(&position) != RIGHTMOST_BUTTON_PRESSED);
                        setboard(hOUT, &board);
                        init_lines(&lines);
                    }
                    SetConsoleTitle("现在轮到你的黑子下了");
                    break;
                case GAMEOVER:
                    SetConsoleTitle("赢，黑子胜，右键重开");
                    while (click(&position) != RIGHTMOST_BUTTON_PRESSED);
                    setboard(hOUT, &board);
                    init_lines(&lines);
                    break;
                default: break;
            }
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

DWORD click(COORD *position) {
    DWORD number;
    INPUT_RECORD buffer;
    ReadConsoleInput(hIN, &buffer, 1, &number);
    if (buffer.EventType == MOUSE_EVENT) {
        (*position) = buffer.Event.MouseEvent.dwMousePosition;
        return buffer.Event.MouseEvent.dwButtonState;
    }
    else return 0;
}
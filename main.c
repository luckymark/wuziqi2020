#include "board.h"
#include "brain.h"

HANDLE hOUT, hIN;
Board board;
Lines lines;

void init();
DWORD click(COORD *position);

int main() {
    init();
    int count = 0;
    while (1) {
        COORD position;
        if (click(&position) == FROM_LEFT_1ST_BUTTON_PRESSED) {
            int x = position.Y - 1;
            int y = (position.X - 2) / 2;
            if (x >= 0 && y >= 0 && x < MAX_X && y < MAX_Y) {
                if (++count % 2) putchess(hOUT, &board, x, y, BLACK);
                else             putchess(hOUT, &board, x, y, WHITE);
            }
        }
    }
    return 0;
}

void init() {
    hOUT = GetStdHandle(STD_OUTPUT_HANDLE);
    hIN  = GetStdHandle(STD_INPUT_HANDLE);
    setboard(hOUT, &board);
    preprocess();
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
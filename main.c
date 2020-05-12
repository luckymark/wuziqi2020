#include "board.h"
#include "brain.h"

HANDLE hOUT, hIN;
Board board;

int main() {
    hOUT = GetStdHandle(STD_OUTPUT_HANDLE);
    hIN  = GetStdHandle(STD_INPUT_HANDLE);
    setboard(hOUT, &board);
    int count = 0;
    while (1) {
        DWORD number;
        INPUT_RECORD buffer;
        ReadConsoleInput(hIN, &buffer, 1, &number);
        if (
            buffer.EventType == MOUSE_EVENT &&
            buffer.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
        ) {
            COORD position = buffer.Event.MouseEvent.dwMousePosition;
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
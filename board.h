#include <Windows.h>
#define MAX_X 15
#define MAX_Y 15

typedef enum { NONE, BLACK, WHITE } chess;
typedef struct {
    chess a[MAX_X][MAX_Y];
} Board;

void setboard(HANDLE h, Board *board);
void putchess(HANDLE h, Board *board, int x, int y, chess c);
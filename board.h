#include <Windows.h>
#define MAX_X 15
#define MAX_Y 15
#define LOG 0 // 0=off 1=on
#define FILENAME "checkmate.log"

typedef enum { OCCUPIED, AVAILABLE, GAMEOVER} status;
typedef enum { NONE, BLACK, WHITE } chess;
typedef struct {
    chess a[MAX_X][MAX_Y];
} Board;

void setboard(HANDLE h, Board *board);
status putchess(HANDLE h, Board *board, int x, int y, chess c);
#include "evalute.h"
#include "define_var.h"

struct gen_loca
{
    int x, y;
    int point;
};

void GetLocation(int map[][MAXN], int color, int* total,gen_loca board[MAXN*MAXN]);
//void SortPoint(int start, int end, struct gen_loca* p);
int FindValid(int x, int y, int map[][MAXN]);
int Max(int x, int y);
int Min(int x, int y);
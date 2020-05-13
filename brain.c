#include "brain.h"
#include <string.h>     /*memset*/

static int score[POW3]; // 预处理一列十五个位置放置棋子的所有情况对应的分数
static int pow3 [MAXN]; // 记录三的零到十四次方 3^0, 3^1, 3^2, 3^3, 3^4, ...
static int add1 [MAXN]; // 记录三进制下的重复1 ()3, (1)3, (11)3, (111)3, ...

#define GET(a, x, y) (a[0][x] / pow3[x] % 3)    // 取出棋盘上(x,y)处的值
#define ISFREE(p, x, y) (!GET((*p).b, x, y) && !GET((*p).w, x, y))
#define PUT(p, x, y, c) do {\
    \
} while(0) 

void minimax(Lines *lines, int depth, int score, int alpha, int beta) {
    if (depth > 4) return;
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            if (ISFREE(lines, i, j)) {
                
            }
        }
    }
}

void putchess_inlines(Lines *lines, int x, int y, int c) {
    if (ISFREE(lines, x, y));
}

void preprocess() {
    pow3[0] = 1, add1[0] = 0;
    for (int i = 1; i < MAXN; i++) {
        pow3[i] = pow3[i - 1] * 3;
        add1[i] = add1[i - 1] * 3 + 1;
    }
    for (int i = 0; i < POW3; i++) {
        
    }
}
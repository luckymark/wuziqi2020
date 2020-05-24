#include "brain.h"
#include <stdlib.h>
#include <string.h>             /*memset&strlen*/

static int basic[POW3_7][2];    // [][0]:棋形长度 [][1]:棋形分数
static int score[POW3];         // 预处理一列十五个位置放置棋子的所有情况对应的分数
static int pow3 [MAXN];         // 记录三的零到十四次方 3^0, 3^1, 3^2, 3^3, 3^4, ...
static int rpt2 [MAXN];         // 记录三进制下的重复2 ()3, (2)3, (22)3, (222)3, ...

#define ABS(x)           ((x) >  0  ? (x) :-(x))
#define MAX(x, y)        ((x) > (y) ? (x) : (y))
#define MIN(x, y)        ((x) < (y) ? (x) : (y))
#define GET(a, x, y)     (a[0][x] / pow3[y] % 3)    // 取出棋盘上(x,y)处的值
#define GETPART(i, j, k) (i / pow3[j] % pow3[k])    // 取i从第j位开始的k个数
#define ISFREE(p, x, y)  (!GET((*p).b, x, y) && !GET((*p).w, x, y))
#define PUT(n, x, c)     do { n += c * pow3[x]; } while (0)
#define SCORE(a, b, x, y)   (\
    score[ a[0][x         ] + 2 * b[0][x         ]] +\
    score[ a[1][y         ] + 2 * b[1][y         ]] +\
    score[(a[2][x+y       ] + 2 * b[2][x+y       ]) * pow3[ABS(MAXN-x-y-1)] + rpt2[ABS(MAXN-x-y-1)]] +\
    score[(a[3][y-x+MAXN-1] + 2 * b[3][y-x+MAXN-1]) * pow3[ABS(y-x       )] + rpt2[ABS(y-x       )]]\
)   // a为己方数组 b为敌方数组 计算以(x,y)为中心点辐射开的四条轴线上己方棋子的分数

static void putchess_color(int color[][MAXN * 2], int x, int y, int delta) {
    PUT(color[0][x], y, delta);                                               // - 横
    PUT(color[1][y], x, delta);                                               // | 竖
    PUT(color[2][x + y           ], x + y < MAXN ? x : MAXN - x - 1, delta);  // / 斜杠
    PUT(color[3][y - x + MAXN - 1],     y > x    ? x : MAXN - x - 1, delta);  // \ 反斜杠
}

void putchess_lines(Lines *lines, int x, int y, int c) {
    if (ISFREE(lines, x, y)) {
        //printf("%d,%d", x, y);
        if (c == 1) putchess_color((*lines).b, x, y, 1);
        if (c == 2) putchess_color((*lines).w, x, y, 1);
    }
}

int cmp(const void *a, const void *b) {
    return ((int *)b)[0] - ((int *)a)[0];
}

static void generate(Lines *lines) {
    int k = 0;
    int visited[MAXN][MAXN];
    memset(visited, 0, sizeof(visited));
    for (int I = 0; I < MAXN; I++) {
        for (int J = 0; J < MAXN; J++) {
            if (!ISFREE(lines, I, J)) {
                for (int i = MAX(0, I - RADIUS); i <= MIN(MAXN - 1, I + RADIUS); i++) {
                    for (int j = MAX(0, J - RADIUS); j <= MIN(MAXN - 1, J + RADIUS); j++) {
                        if(!visited[i][j] && ISFREE(lines, i, j)) {
                            (*lines).points[k][0]  = SCORE((*lines).b, (*lines).w, i, j);
                            (*lines).points[k][0] -= SCORE((*lines).w, (*lines).b, i, j);
                            putchess_color((*lines).w, i, j,  1);
                            (*lines).points[k][0] += SCORE((*lines).w, (*lines).b, i, j);
                            (*lines).points[k][0] -= SCORE((*lines).b, (*lines).w, i, j);
                            putchess_color((*lines).w, i, j, -1);
                            (*lines).points[k][1] = i;
                            (*lines).points[k][2] = j;
                            visited[i][j] = 1;
                            k++;
                        }
                    }
                }
            }
        }
    }
    (*lines).number = k - 1;
    qsort((*lines).points, k, sizeof((*lines).points[0]), cmp);
}

MinimaxInfo minimax(Lines *lines, int depth, int scoreFin, int alpha, int beta) {
    if (depth == 1) {
        generate(lines);
    }
    MinimaxInfo info;
    info.alpha = alpha, info.beta = beta;
    info.x = (*lines).points[0][1], info.y = (*lines).points[0][2];
    const int from = depth % 2 == 0 ? MIN(POINTS, (*lines).number) : 0;
    const int to   = depth % 2 == 0 ? -1 : MIN(POINTS, (*lines).number) + 1;
    const int dk   = depth % 2 == 0 ? -1 : 1;
    for (int k = from; k != to; k += dk) {
        const int i = (*lines).points[k][1];
        const int j = (*lines).points[k][2];
        if (ISFREE(lines, i, j)) {
            // 尝试放置该棋子前的分数
            int scoreCom = -SCORE((*lines).w, (*lines).b, i, j);
            int scoreHum = -SCORE((*lines).b, (*lines).w, i, j);
            // 尝试放置棋子，偶数层是玩家：放黑子，奇数层是机器：放白子
            putchess_color(depth % 2 == 0 ? (*lines).b : (*lines).w, i, j, 1);
            // 放置棋子后的分数，计算前后差量：后减前
            scoreCom += SCORE((*lines).w, (*lines).b, i, j);
            scoreHum += SCORE((*lines).b, (*lines).w, i, j);
            scoreFin += scoreCom - scoreHum;
            // 向下搜索
            if (depth == DEPTH || scoreCom > 1e6 || scoreHum > 1e6) { // 搜到最大深度或有一方出现活4或连5
                info.alpha = MAX(info.alpha, scoreFin);
                info.beta  = MIN(info.beta , scoreFin);
            }
            else {
                MinimaxInfo son_info = minimax(lines, depth + 1, scoreFin, info.alpha, info.beta);
                if (depth % 2 == 0) {
                    if (son_info.alpha < info.beta) {
                        info.beta = son_info.alpha;
                        info.x = i, info.y = j;
                    }
                }
                else {
                    if (son_info.beta > info.alpha) {
                        info.alpha = son_info.beta; 
                        info.x = i, info.y = j;
                    }
                }
            }
            // 还原现场
            scoreFin -= scoreCom - scoreHum;
            putchess_color(depth % 2 == 0 ? (*lines).b : (*lines).w, i, j, -1);
            if (info.alpha >= info.beta) return info;
        }
    }
    return info;
}

static void loadbasic(char threes[], int score) {
    int ternary[2] = {0, 0};
    int length = strlen(threes);
    for (int i = 0; i < length; i++) {
        ternary[0] = ternary[0] * 3 - '0' + threes[i];
        ternary[1] = ternary[1] * 3 - '0' + threes[length - i - 1];
    }
    basic[ternary[0]][0] = basic[ternary[1]][0] = length;
    basic[ternary[0]][1] = basic[ternary[1]][1] = score;
}

static void loaddata() {
    loadbasic("11111"  , 1e8); // 连五
    loadbasic("011110" , 1e7); // 活四
    loadbasic("011112" , 1e5); // 冲四
    loadbasic("10111"  , 1e5); //
    loadbasic("11011"  , 1e5); //
    loadbasic("01110"  , 1e4); // 活三
    loadbasic("10110"  , 1e4); //
    loadbasic("01011"  , 1e4); //
    loadbasic("001112" , 1e3); // 眠三
    loadbasic("010112" , 1e3); //
    loadbasic("011012" , 1e3); //
    loadbasic("100112" , 1e3); //
    loadbasic("10101"  , 1e3); //
    loadbasic("2011102", 1e3); //
    loadbasic("001100" , 1e2); // 活二
    loadbasic("01010"  , 1e2); //
    loadbasic("010010" , 1e2); //
    loadbasic("000112" , 1e1); // 眠二
    loadbasic("001012" , 1e1); //
    loadbasic("010012" , 1e1); //
    loadbasic("10001"  , 1e1); //
    loadbasic("00001"  , 1e0); // 活一
    loadbasic("00010"  , 1e0); //
    loadbasic("00100"  , 1e0); //
}

void preprocess() {
    loaddata();
    pow3[0] = 1, rpt2[0] = 0;
    for (int i = 1; i < MAXN; i++) {
        pow3[i] = pow3[i - 1] * 3;
        rpt2[i] = rpt2[i - 1] * 3 + 2;
    }
    for (int i = 0; i < POW3; i++) {
        for (int j = 0; j <= MAXN - 5; j++) {
            for (int k = 5; k <= MIN(7, MAXN - j); k++) {
                int ternary = GETPART(i, j, k);
                if (basic[ternary][0] == k) {
                    score[i] += basic[ternary][1];
                }
            }
        }
    }
}

void init_lines(Lines *lines) {
    memset((*lines).b, 0, sizeof((*lines).b));
    memset((*lines).w, 0, sizeof((*lines).w));
}
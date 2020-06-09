#include "brain.h"
#include <stdlib.h>
#include <string.h>             /*memset&strlen*/

static int basic[POW3_7][2];    // [][0]:棋形长度 [][1]:棋形分数
static int score[POW3];         // 预处理一列十五个位置放置棋子的所有情况对应的分数
static int pow3 [MAXN];         // 记录三的零到十四次方 3^0, 3^1, 3^2, 3^3, 3^4, ...
static int rpt2 [MAXN];         // 记录三进制下的重复2 ()3, (2)3, (22)3, (222)3, ...
static int b33, b34, b44, w33, w34, w44;

#define ls                      (*lines)
#define ABS(x)                  ((x) >  0  ? (x) :-(x))
#define MAX(x, y)               ((x) > (y) ? (x) : (y))
#define MIN(x, y)               ((x) < (y) ? (x) : (y))
#define GET(a, x, y)            (a[0][x] / pow3[y] % 3)    // 取出棋盘上(x,y)处的值
#define GETPART(i, j, k)        (i / pow3[j] % pow3[k])    // 取i从第j位开始的k个数
#define ISFREE(p, x, y)         (!GET((*p).b, x, y) && !GET((*p).w, x, y))
#define PUT(n, x, c)            do { n += c * pow3[x]; } while (0)
#define SCORE(a, b, x, y, k)    (\
    (((k)&(1<<0))>>0) * (score[ a[0][x         ] + 2 * b[0][x         ]]) +\
    (((k)&(1<<1))>>1) * (score[ a[1][y         ] + 2 * b[1][y         ]]) +\
    (((k)&(1<<2))>>2) * (score[(a[2][x+y       ] + 2 * b[2][x+y       ]) * pow3[ABS(MAXN-x-y-1)] + rpt2[ABS(MAXN-x-y-1)]]) +\
    (((k)&(1<<3))>>3) * (score[(a[3][y-x+MAXN-1] + 2 * b[3][y-x+MAXN-1]) * pow3[ABS(y-x       )] + rpt2[ABS(y-x       )]])  \
)   // a为己方数组 b为敌方数组 计算以(x,y)为中心点辐射开的四条轴线上己方棋子的分数

static void count_34(int dscore, int *three, int *four);
static void putchess_color(Lines *lines, int color[][MAXN * 2], int x, int y, int delta);
static void bonus(Lines *lines, int scoreHum, int scoreCom, int *scrDelta, int ddepth);
static void loadbasic(char threes[], int score);
int cmp(const void *a, const void *b);
static void generate(Lines *lines);
static void loaddata();

static void putchess_color(Lines *lines, int color[][MAXN * 2], int x, int y, int delta) {
    int dscore_w[4], dscore_b[4];
    for (int i = 0; i < 4; i++) {
        dscore_b[i] = -SCORE(ls.b, ls.w, x, y, 1<<i);
        dscore_w[i] = -SCORE(ls.w, ls.b, x, y, 1<<i);
    }
    PUT(color[0][x], y, delta);                                               // - 横
    PUT(color[1][y], x, delta);                                               // | 竖
    PUT(color[2][x + y           ], x + y < MAXN ? x : MAXN - x - 1, delta);  // / 斜杠
    PUT(color[3][y - x + MAXN - 1],     y > x    ? x : MAXN - x - 1, delta);  // \ 反斜杠
    for (int i = 0; i < 4; i++) {
        dscore_b[i] += SCORE(ls.b, ls.w, x, y, 1<<i);
        dscore_w[i] += SCORE(ls.w, ls.b, x, y, 1<<i);
        count_34(dscore_b[i], &ls.b3, &ls.b4);
        count_34(dscore_w[i], &ls.w3, &ls.w4);
    }
}

static void count_34(int dscore, int *three, int *four) {
    int th = 0, fo = 0;
    while (dscore >  1e8) dscore -= 1e8;
    while (dscore < -1e8) dscore += 1e8;
    while (dscore >  1e6) dscore -= 1e7;
    while (dscore < -1e6) dscore += 1e7;
    while (dscore >  8e3) dscore -= 1e4, fo++;
    while (dscore < -8e3) dscore += 1e4, fo--;
    while (dscore >  8e2) dscore -= 1e3, th++;
    while (dscore < -8e2) dscore += 1e3, th--;
    if (fo)
        (*four)  += fo > 0 ? 1 : -1;
    else if (th)
        (*three) += th > 0 ? 1 : -1;
}

void putchess_lines(Lines *lines, int x, int y, int c) {
    if (ISFREE(lines, x, y)) {
        if (c == 1) {   // Black
            putchess_color(lines, ls.b, x, y, 1);
        }
        if (c == 2) {   // White
            putchess_color(lines, ls.w, x, y, 1);
        }
    }
}

int cmp(const void *a, const void *b) {
    return ((int *)b)[0] - ((int *)a)[0];
}

static void generate(Lines *lines) {
    int k = 0;
    int visited[MAXN][MAXN];
    memset(visited, 0, sizeof(visited));
    const int b3 = ls.b3, b4 = ls.b4, w3 = ls.w3, w4 = ls.w4;
    for (int I = 0; I < MAXN; I++) {
        for (int J = 0; J < MAXN; J++) {
            if (!ISFREE(lines, I, J)) {
                for (int i = MAX(0, I - RADIUS); i <= MIN(MAXN - 1, I + RADIUS); i++) {
                    for (int j = MAX(0, J - RADIUS); j <= MIN(MAXN - 1, J + RADIUS); j++) {
                        if(!visited[i][j] && ISFREE(lines, i, j)) {
                            ls.points[k][0]  = SCORE(ls.b, ls.w, i, j, 15);
                            ls.points[k][0] -= SCORE(ls.w, ls.b, i, j, 15);
                            putchess_color(lines, ls.w, i, j,  1);
                            ls.points[k][0] += SCORE(ls.w, ls.b, i, j, 15);
                            ls.points[k][0] -= SCORE(ls.b, ls.w, i, j, 15);
                            putchess_color(lines, ls.w, i, j, -1);
                            ls.points[k][1] = i;
                            ls.points[k][2] = j;
                            visited[i][j] = 1;
                            k++;
                        }
                    }
                }
            }
        }
    }
    ls.number = k - 1;
    ls.b3 = b3, ls.b4 = b4, ls.w3 = w3, ls.w4 = w4;
    qsort(ls.points, k, sizeof(ls.points[0]), cmp);
}

static void bonus(Lines *lines, int scoreHum, int scoreCom, int *scrDelta, int ddepth) {
    if (scoreHum  > 1e8)
        *scrDelta -= 9e9 * ddepth;
    if (scoreCom  > 1e8)
        *scrDelta += 9e9 * ddepth;
    if (scoreHum  > 1e6 && scoreHum < 1e8)
        *scrDelta -= 2e7 * ddepth;
    if (scoreCom  > 1e6 && scoreCom < 1e8)
        *scrDelta += 2e7 * ddepth;
    if (ls.b4 >= 2 && !b44)
        *scrDelta -= 2e7 * ddepth, b44 = 1;
    if (ls.w4 >= 2 && !w44)
        *scrDelta += 2e7 * ddepth, w44 = 1;
    if (ls.b3 && ls.b4 && !b34)
        *scrDelta -= 2e5 * ddepth, b34 = 1;
    if (ls.w3 && ls.w4 && !w34)
        *scrDelta += 2e5 * ddepth, w34 = 1;
    if (ls.b3 >= 2 && !b33)
        *scrDelta -= 2e5 * ddepth, b33 = 1;
    if (ls.w3 >= 2 && !w33)
        *scrDelta += 2e5 * ddepth, w33 = 1;
}

MinimaxInfo minimax(Lines *lines, int depth, long long scoreFin, long long alpha, long long beta) {
    if (depth == 1) {
        b33 = w33 = b34 = w34 = b44 = w44 = 0;
        generate(lines);
        alpha *= oo;
        beta  *= oo;
    }
    MinimaxInfo info;
    info.alpha = alpha, info.beta = beta;
    info.x = ls.points[0][1], info.y = ls.points[0][2];
    const int b3 = ls.b3, b4 = ls.b4, w3 = ls.w3, w4 = ls.w4;
    for (int k = 0; k != MIN(POINTS, ls.number); k++) {
        const int i = ls.points[k][1];
        const int j = ls.points[k][2];
        if (ISFREE(lines, i, j)) {
            int scoreCom = -SCORE(ls.w, ls.b, i, j, 15);                    // 尝试放置该棋子前的分数
            int scoreHum = -SCORE(ls.b, ls.w, i, j, 15);
            putchess_color(lines, depth % 2 == 0 ? ls.b : ls.w, i, j, 1);   // 尝试放置棋子，偶数层是玩家：放黑子，奇数层是机器：放白子
            scoreCom += SCORE(ls.w, ls.b, i, j, 15);                        // 放置棋子后的分数，计算前后差量：后减前
            scoreHum += SCORE(ls.b, ls.w, i, j, 15);
            scoreFin += scoreCom - scoreHum;
            int scrDelta = 0;
            
            if (depth == 1 && scoreCom > 1e8) {                             // 向下搜索
                info.x = i, info.y = j;
                return info;
            }
            else {
                const int b33_ = b33, b34_ = b34, b44_ = b44;
                const int w33_ = w33, w34_ = w34, w44_ = w44;
                
                bonus(lines, scoreHum, scoreCom, &scrDelta, DEPTH - depth + 1);
                scoreFin += scrDelta;
                if (depth == DEPTH/* || scoreCom > 1e8 || scoreHum > 1e8*/) {
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
                b33 = b33_, b34 = b34_, b44 = b44_;
                w33 = w33_, w34 = w34_, w44 = w44_;
            }
            scoreFin -= scoreCom - scoreHum + scrDelta;                     // 还原现场
            putchess_color(lines, depth % 2 == 0 ? ls.b : ls.w, i, j, -1);
            ls.b3 = b3, ls.b4 = b4, ls.w3 = w3, ls.w4 = w4;
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
    loadbasic("11111"  , 1e9); // 连五
    loadbasic("011110" , 1e7); // 活四
    //                 , 1e7); // 双四
    //                 , 1e5); // 三四
    //                 , 1e5); // 双三
    loadbasic("011112" , 1e4); // 冲四
    loadbasic("10111"  , 1e4); //
    loadbasic("11011"  , 1e4); //
    loadbasic("01110"  , 1e3); // 活三
    loadbasic("010110" , 1e3); //
    loadbasic("210110" , 1e3); //
    loadbasic("010112" , 1e3); //
    loadbasic("001112" , 1e2); // 眠三
    loadbasic("010112" , 1e2); //
    loadbasic("011012" , 1e2); //
    loadbasic("100112" , 1e2); //
    loadbasic("10101"  , 1e2); //
    loadbasic("2011102", 1e2); //
    loadbasic("001100" , 1e1); // 活二
    loadbasic("01010"  , 1e1); //
    loadbasic("010010" , 1e1); //
    loadbasic("000112" , 3e0); // 眠二
    loadbasic("001012" , 3e0); //
    loadbasic("010012" , 3e0); //
    loadbasic("10001"  , 3e0); //
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
    memset(ls.b, 0, sizeof(ls.b));
    memset(ls.w, 0, sizeof(ls.w));
    ls.b3 = ls.w3 = ls.b4 = ls.w4 = 0;
}
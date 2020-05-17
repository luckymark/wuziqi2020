#define POW3 14348907   // 3^15
#define POW3_7 2187     // 3^7
#define oo (1<<30)
#define POINTS 100
#define RADIUS 4
#define DEPTH 4         // 必须是偶数
#define MAXN 15

typedef struct {
    int b[4][MAXN * 2];
    int w[4][MAXN * 2];
    int points[MAXN * MAXN][3];
    int number;
} Lines;

typedef struct {
    int x, y, alpha, beta;
} MinimaxInfo;

void preprocess();
void init_lines(Lines *lines);
void putchess_lines(Lines *lines, int x, int y, int c);
MinimaxInfo minimax(Lines *lines, int depth, int score, int alpha, int beta);
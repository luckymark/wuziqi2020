#define POW3 14348907 // 3^15
#define MAXN 15

typedef struct {
    int b[4][MAXN];
    int w[4][MAXN];
} Lines;

void preprocess();
void minimax(Lines *lines, int depth, int score, int alpha, int beta);
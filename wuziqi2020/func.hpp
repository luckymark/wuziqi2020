#include "draw.hpp"
#include <time.h>

// 各种棋子连成线的评分
#define FIVE 10000000  // 五子
#define L4 100000  // 活四
#define L3 1000  // 活三
#define L2 100     // 活二
#define L1 10      // 活一
#define S4 1000   // 眠四
#define S3 100   // 眠三
#define S2 10      // 眠二
#define S1 1
#define NOUSE 0

// 棋子颜色的值
#define BLACK_C 1    // 黑色
#define WHITE_C 0    // 白色
#define EMPTY_C -1   // 空

// 最大最小值搜索层数(必须为偶数)
#define LAYER_LIMIT 4
// 相同分值的点位个数的最大值
#define COUNT_BEST_MAX 10

// 全局变量
extern box BOX[15][15];     // 棋盘
extern int di[4];    // - | \ / 四个方向
extern int dj[4];	// - | \ / 四个方向
extern int evaluate_map[3][5];// 评分表 [敌方子数][我方子数] 
//extern int step; // 步数（棋子数）
//extern seat steps[225];

// 函数声明

// math
bool inBOX(int i, int j);
void setColor(int i, int j, int color);
int compare(int x, int y, bool bigger);
bool isColor(int i, int j, int color);
bool have_neighbor55(int i, int j);
int paritition(seat A[], int low, int high);
void quickSort(seat A[], int low, int high);

// getPosition
int max_min_search(int color, int alpha, int beta, int depth);
int evaluate_score(int color);
int evaluate_score_one(int b_i, int b_j, int color);
void gen(seat a[], int color);
#include "draw.hpp"

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
// 每层搜索个数最大值
#define SEARCH_NUM_MAX 10

// 全局变量
extern box BOX[15][15];     // 棋盘
extern int di[4];    // - | \ / 四个方向
extern int dj[4];	// - | \ / 四个方向
extern int evaluate_map[3][5];// 评分表 [敌方子数][我方子数] 

// 函数声明
// math.cpp
void quickSort(seat A[], int low, int high);
int evaluate_score_one(int b_j, int color, int b_i);
#define inBOX(i,j) ((i) >= 0 && (j) >= 0 && (i) <= 14 && (j) <= 14)
#define isColor(i,j,color) (BOX[(i)][(j)].color_val == (color))
#define setColor(i,j,color) (BOX[(i)][(j)].color_val = (color))
#define bigger(x,y) (((x) > (y)) ? (x) : (y))
#define smaller(x,y) (((x) < (y)) ? (x) : (y))
// 更新后的neighbor函数
#define ADD_NEIGHBOR 1
#define DES_NEIGHBOR -1
void set_neighbor(int i, int j, int type);
extern int neighbor[15][15];
#define have_neighbor(i,j) (neighbor[(i)][(j)] > 0)

// getPosition.cpp
int max_min_search(int color, int alpha, int beta, int depth);
#include "func.hpp"
#include <time.h>

// 全局变量
extern box BOX[15][15];     // 棋盘
int di[4] = { 0,1,1,1 };    // - | \ / 四个方向
int dj[4] = { 1,0,1,-1 };	// - | \ / 四个方向
int evaluate_map[3][5] = {  // 评分表 [敌方子数][我方子数] 
	{L1 ,L2, L3, L4, FIVE},
	{S1, S2, S3, S4, FIVE},
	{0, 0, 0, 0, FIVE}
};

// 接口函数
seat findbestseat(int color)
{
	seat best[COUNT_BEST_MAX];
	int count_best = 0;

	// MIN MAX SEARCH
	int score = INT_MIN;
	seat a[15 * 15];
	int count = gen(a, color);
	// 黑科技 -- 10次
	for (int i = 0; i < count; i++) {
		if (a[i].myscore >= FIVE) {
			return a[i];
		}
		setColor(a[i].i, a[i].j, color);
		set_neighbor(a[i].i, a[i].j, ADD_NEIGHBOR);
		int temp = max_min_search(1 - color, INT_MIN, INT_MAX, LAYER_LIMIT - 1);
		set_neighbor(a[i].i, a[i].j, DES_NEIGHBOR);
		setColor(a[i].i, a[i].j, EMPTY_C);
		if (best[0].score <= temp) {
			if (best[0].score < temp) {
				count_best = 0;
				best[0].score = temp;
			}
			else if (best[0].score == temp && count_best != COUNT_BEST_MAX - 1) {
				count_best++;
			}
			best[count_best].i = a[i].i;
			best[count_best].j = a[i].j;
		}
	}
	srand(time(NULL));
	return best[rand() % (count_best + 1)];
}
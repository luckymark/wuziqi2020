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
seat findbestseat2(int color)
{
	seat best[COUNT_BEST_MAX];
	int count_best = 0;

	// MIN MAX SEARCH
	int dump = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (isColor(i, j, EMPTY_C) && have_neighbor55(i, j)) {
				setColor(i, j, color);
				dump = max_min_search(1 - color, INT_MIN, INT_MAX, LAYER_LIMIT - 1);
				setColor(i, j, EMPTY_C);
				if (best[count_best].score < dump) {
					count_best = 0;
					best[0].score = dump;
					best[0].i = i;
					best[0].j = j;
				}
				else if(best[count_best].score == dump && count_best != COUNT_BEST_MAX - 1){
					count_best++;
					best[count_best].score = dump;
					best[count_best].i = i;
					best[count_best].j = j;
				}				
			}
		}
	}
	srand(time(NULL));
	return best[rand() % (count_best + 1)]; 
}


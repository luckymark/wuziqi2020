#include "func.hpp"
#include <time.h>


// 各种棋子连成线的评分
#define FIVE 10000000  // 五子
#define LFORE 100000  // 活四
#define LTHREE 1000  // 活三
#define LTWO 100     // 活二
#define LONE 10      // 活一
#define SFORE 1000   // 眠四
#define STHREE 100   // 眠三
#define STWO 10      // 眠二
#define SONE 1

// 棋子颜色的值
#define BLACK_C 1    // 黑色
#define WHITE_C 0    // 白色
#define EMPTY_C -1   // 空

// 最大最小值搜索层数(必须为偶数)
// 4层已经比较快了，但下到后面会比较慢
#define LAYER_LIMIT 4
// 相同分值的点位个数的最大值
#define COUNT_BEST_MAX 10

// 全局变量
extern box BOX[15][15];     // 棋盘
int di[4] = { 0,1,1,1 };    // - | \ / 四个方向
int dj[4] = { 1,0,1,-1 };	// - | \ / 四个方向
int evaluate_map[3][5] = {  // 评分表 [敌方子数][我方子数] 
	{LONE ,LTWO, LTHREE, LFORE, FIVE},
	{SONE, STWO, STHREE, SFORE, FIVE},
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
				setColor(i, j, EMPTY_C);
			}
		}
	}
	srand(time(NULL));
	return best[rand() % (count_best + 1)]; 
}

// 最大最小值搜索
// alpha-beta 剪枝优化 (提升也不大)
// have_seat55 判断棋子优化
// 启发式函数优化(依旧慢，且层数没有提升)
int max_min_search(int color, int alpha, int beta, int depth)
{
	if (depth == 0) return evaluate_score(color);
	int score = (depth % 2 == 0) ? INT_MIN : INT_MAX;
	int dump;
	seat a[15 * 15];
	gen(a, color);
	for (int i = 0; i < 15 * 15; i++) {
		if (isColor(a[i].i, a[i].j, EMPTY_C) && have_neighbor55(a[i].i, a[i].j)) {
			setColor(a[i].i, a[i].j, color);
			dump = max_min_search(1 - color, alpha, beta, depth - 1);
			if (depth % 2 == 0) {
				score = compare(score, dump, true);
				alpha = compare(alpha, dump, true);
			}
			else {
				score = compare(score, dump, false);
				beta = compare(beta, dump, false);
			}
			setColor(a[i].i, a[i].j, EMPTY_C);
			if (alpha >= beta) return score;
		}
	}
	return score;
}

// 启发式评估函数
// 便于优先搜索分数高的，加快AB剪枝速度
void gen(seat a[], int color) 
{
	for (int i = 0; i < 15 * 15; i++) {
		a[i].i = i / 15;
		a[i].j = i % 15;
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (isColor(i, j, EMPTY_C)) {
				setColor(i, j, color);
				a[i * 15 + j].score = evaluate_score_one(color, i, j);
				setColor(i, j, 1 - color);
				a[i * 15 + j].score += evaluate_score_one(color, i, j);
				setColor(i, j, EMPTY_C);
			}
		}
	}
	quickSort(a, 0, 15 * 15 - 1);
}


// 整个棋盘评分 -- 综合黑白棋子的棋盘总分
// 棋面越利于color，分数越大
int evaluate_score(int color)
{
	int score = 0;
	for (int b_i = 0; b_i < 15; b_i++) {
		for (int b_j = 0; b_j < 15; b_j++) {
			if (BOX[b_i][b_j].color_val == color) {
				score += evaluate_score_one(color, b_i, b_j);
			}
			else if (BOX[b_i][b_j].color_val == 1 - color) {
				score -= evaluate_score_one(1 - color, b_i, b_j);
			}
		}
	}
	return score;
}
 
// 单个棋子评分
int evaluate_score_one(int color, int b_i, int b_j)
{
	int cur_i;
	int cur_j;
	int score = 0;
	for (int i = 0; i < 4; i++) {
		// 判断当前状况
		int count_my = -1;
		int count_enemy = 0;
		cur_i = b_i;
		cur_j = b_j;
		while (isColor(cur_i,cur_j,color) && inBOX(cur_i,cur_j)) {		
			count_my++;
			cur_i -= di[i];
			cur_j -= dj[i];
		}
		if (isColor(cur_i, cur_j, 1 - color) || !inBOX(cur_i, cur_j)) {
			count_enemy++;
		}
		cur_i = b_i;
		cur_j = b_j;
		while (isColor(cur_i, cur_j, color) && inBOX(cur_i,cur_j)) {
			count_my++;
			cur_i += di[i];
			cur_j += dj[i];
		}
		if (isColor(cur_i, cur_j, 1 - color) || !inBOX(cur_i, cur_j)) {
			count_enemy++;
		}
		// 判定分数
		if (count_my > 5) {
			count_my = 5;
		}
		if (count_enemy > 2) {
			count_enemy = 2;
		}
		score += evaluate_map[count_enemy][count_my - 1];
	}
	return score;
}
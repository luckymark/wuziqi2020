#include "func.hpp"
#include <stdio.h>

// 启发式评估函数
// 便于优先搜索分数高的，加快AB剪枝速度
static void gen(seat a[], int color)
{
	int count = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (isColor(i, j, EMPTY_C) && have_neighbor(i, j)) {
				a[count].i = i;
				a[count].j = j;
				setColor(i, j, color);
				a[count].score = evaluate_score_one(i, j, color);
				setColor(i, j, 1 - color);
				a[count].score += evaluate_score_one(i, j, 1 - color);
				setColor(i, j, EMPTY_C);
				count++;
			}
		}
	}
	quickSort(a, 0, count);
}

// 整个棋盘评分 -- 综合黑白棋子的棋盘总分
// 棋面越利于color，分数越大
static int evaluate_score(int color)
{
	int score = 0;
	for (int b_i = 0; b_i < 15; b_i++) {
		for (int b_j = 0; b_j < 15; b_j++) {
			if (!isColor(b_i, b_j, EMPTY_C)) {
				if (isColor(b_i, b_j, color)) {
					score += evaluate_score_one(b_i, b_j, color);
				}
				else {
					score -= evaluate_score_one(b_i, b_j, 1 - color);
				}
			}
		}
	}
	return score;
}

// 最大最小值搜索
// alpha-beta 剪枝优化
// have_neighbor 判断棋子优化
// 启发式函数优化
int max_min_search(int color, int alpha, int beta, int depth)
{
	if (depth == 0) return evaluate_score(color);
	int score = (depth % 2 == 0) ? INT_MIN : INT_MAX;
	int temp;
	seat a[15 * 15];
	gen(a, color);
	// 黑科技 -- 10次
	for (int i = 0; i < SEARCH_NUM_MAX; i++) {
		setColor(a[i].i, a[i].j, color);
		set_neighbor(a[i].i, a[i].j, ADD_NEIGHBOR);
		temp = max_min_search(1 - color, alpha, beta, depth - 1);
		set_neighbor(a[i].i, a[i].j, DES_NEIGHBOR);
		setColor(a[i].i, a[i].j, EMPTY_C);
		if (depth % 2 == 0) {
			score = bigger(score, temp);
			alpha = bigger(alpha, temp);
		}
		else {
			score = smaller(score, temp);
			beta = smaller(beta, temp);
		}
		if (alpha >= beta) return score;
	}
	return score;
}
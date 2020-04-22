#include "func.hpp"
#include <stdio.h>


// 最大最小值搜索
// alpha-beta 剪枝优化 (提升也不大)
// have_seat55 判断棋子优化
// 启发式函数优化(依旧慢，且层数没有提升)
int max_min_search(int color, int alpha, int beta, int depth)
{
	if (depth == 0) return evaluate_score(color);
	int score = (depth % 2 == 0) ? INT_MIN : INT_MAX;
	int temp;
	seat a[15 * 15];
	gen(a, color);
	for (int i = 0; i < 15 * 15; i++) {
		if (isColor(a[i].i, a[i].j, EMPTY_C) && have_neighbor55(a[i].i, a[i].j)) {
			setColor(a[i].i, a[i].j, color);
			temp = max_min_search(1 - color, alpha, beta, depth - 1);
			if (depth % 2 == 0) {
				score = compare(score, temp, true);
				alpha = compare(alpha, temp, true);
			}
			else {
				score = compare(score, temp, false);
				beta = compare(beta, temp, false);
			}
			setColor(a[i].i, a[i].j, EMPTY_C);
			if (alpha >= beta) return score;
		}
	}
	return score;
}

int endSearch(int i, int j, int color)
{
	setColor(i, j, 1 - color);
	return 0;
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
			if (isColor(i, j, EMPTY_C) && have_neighbor55(i,j)) {
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
		while (isColor(cur_i, cur_j, color) && inBOX(cur_i, cur_j)) {
			count_my++;
			cur_i -= di[i];
			cur_j -= dj[i];
		}
		if (isColor(cur_i, cur_j, 1 - color) || !inBOX(cur_i, cur_j)) {
			count_enemy++;
		}
		cur_i = b_i;
		cur_j = b_j;
		while (isColor(cur_i, cur_j, color) && inBOX(cur_i, cur_j)) {
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

// 另一种评估方法
int map[3][3][3][5] = {
	// empty == 0
	{
		//rem   //enemy     0                                  1                                     2
		/*0*/{     { L1,L2,L3,L4,FIVE },               { S1,S2,S3,S4,FIVE },         { NOUSE,NOUSE,NOUSE,NOUSE,FIVE } },
		/*1*/{     { L1,L2,L3,L4,FIVE },          { NOUSE,NOUSE,NOUSE,S4,FIVE },     { NOUSE,NOUSE,NOUSE,NOUSE,NOUSE } },
		/*2*/{    { NOUSE,NOUSE,S3,L4,FIVE },   { NOUSE,NOUSE,NOUSE,NOUSE,NOUSE },   { NOUSE,NOUSE,NOUSE,NOUSE,NOUSE } }
	},
	// empty == 1
	{
		//rem   //enemy     0                                  1                                        2
		/*0*/{    { L1 ,L2, L3, S4, S4 },              { S1, S2, S3, S4, S4 },            { NOUSE,NOUSE,NOUSE,S4,S4 } },
		/*1*/{   { L1 ,L2, L3, L4, FIVE },         { NOUSE, NOUSE, S3, S4, FIVE },      { NOUSE,NOUSE,NOUSE,NOUSE,NOUSE } },
		/*2*/{ { NOUSE, L2, L3, L4, FIVE },     { NOUSE, NOUSE, NOUSE, NOUSE, NOUSE },  { NOUSE,NOUSE,NOUSE,NOUSE,NOUSE } }
	},
	// empty == 2   
	{
		//rem   //enemy     0                                  1                                 2
		/*0*/{ { NOUSE,NOUSE,S3,L3,S4 },            { NOUSE,NOUSE,S3,L3,S4 },          { NOUSE,NOUSE,S3,L3,S4 } },
		/*1*/{ { NOUSE,NOUSE,S3,L3,S4 },            { NOUSE,NOUSE,S3,L3,S4 },        { NOUSE,NOUSE,NOUSE,NOUSE,NOUSE } },
		/*2*/{ { NOUSE,NOUSE,S3,L3,S4 },          { NOUSE,NOUSE,NOUSE,NOUSE,NOUSE },   { NOUSE,NOUSE,NOUSE,NOUSE,NOUSE } }
	}
};
// 另一个单子评估函数
int get_score(int i, int j, int color)
{
	int score = 0;
	int curi;
	int curj;
	int my;
	int enemy;
	int empty;
	int rem_enemy;
	for (int a = 0; a < 4; a++) {
		my = 0;
		enemy = 0;
		empty = 0;
		rem_enemy = 0;
		curi = i;
		curj = j;
		while (1) {
			if (inBOX(curi, curj) && isColor(curi, curj, color)) {
				my++;
			}
			else if (!inBOX(curi, curj) || isColor(curi, curj, 1 - color)) {
				enemy++;
				break;
			}
			else {
				// isColor(curi, curj, EMPTY_C)
				if (inBOX(curi - di[a], curj - dj[a]) && isColor(curi - di[a], curj - dj[a], color)) {
					if (empty != 2) {
						empty++;
					}
					else break;
				}
				else if (!inBOX(curi - di[a], curj - dj[a]) || isColor(curi - di[a], curj - dj[a], 1 - color)) {
					rem_enemy++;
					break;
				}
				else {
					// isColor(curi - di[a], curj - dj[a], EMPTY_C)
					break;
				}
			}
			curi -= di[a];
			curj -= dj[a];
		}
		curi = i + di[a];
		curj = j + dj[a];
		while (1) {
			if (inBOX(curi, curj) && isColor(curi, curj, color)) {
				my++;
			}
			else if (!inBOX(curi, curj) || isColor(curi, curj, 1 - color)) {
				enemy++;
				break;
			}
			else {
				// isColor(curi, curj, EMPTY_C)
				if (inBOX(curi - di[a], curj - dj[a]) && isColor(curi + di[a], curj + dj[a], color)) {
					if (empty != 2) {
						empty++;
					}
					else break;
				}
				else if (!inBOX(curi - di[a], curj - dj[a]) || isColor(curi + di[a], curj + dj[a], 1 - color)) {
					rem_enemy++;
					break;
				}
				else {
					// isColor(curi + di[a], curj + dj[a], EMPTY_C)
					break;
				}
			}
			curi += di[a];
			curj += dj[a];
		}
		if (my > 5) {
			my = 5;
		}
		if (my == 0) {
			return 0;
		}
		score += map[empty][rem_enemy][enemy][my - 1];
	}
	return score;
}

int good_position(int i, int j, int color) 
{
	int score = 0;
	if (isColor(i, j,EMPTY_C)) {
		setColor(i, j, color);
		score += get_score(i, j, color);
		setColor(i, j, 1 - color);
		score += get_score(i, j, 1 - color);
		setColor(i, j, EMPTY_C);
	}
	return score / 2;
}
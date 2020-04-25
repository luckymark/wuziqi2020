#include "func.hpp"

// 优化速度函数 
// 判断最近的 5 * 5 的格子中是否有落子 
int neighbor[15][15] = { 0 }; // 用来判断旁边是否有子(5*5)
void set_neighbor(int i, int j, int type)
{
	for (int a = i - 2; a <= i + 2; a++) {
		for (int b = j - 2; b <= j + 2; b++) {
			if (inBOX(a, b)) {
				neighbor[a][b] += type;
			}
		}
	}
}

// 单个棋子评分
int evaluate_score_one(int b_i, int b_j, int color)
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

static int paritition(seat A[], int low, int high)
{
	seat pivot = A[low];
	while (low < high) {
		while (low < high && A[high].score <= pivot.score) {
			--high;
		}
		A[low] = A[high];
		while (low < high && A[low].score >= pivot.score) {
			++low;
		}
		A[high] = A[low];
	}
	A[low] = pivot;
	return low;
}

// 从大到小排序
void quickSort(seat A[], int low, int high) //快排母函数
{
	if (low < high) {
		int pivot = paritition(A, low, high);
		quickSort(A, low, pivot - 1);
		quickSort(A, pivot + 1, high);
	}
}
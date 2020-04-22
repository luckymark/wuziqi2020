#include "func.hpp"
// 优化速度函数 
// 判断最近的 5 * 5 的格子中是否有落子 
int neighbor[15][15] = { 0 };
void set_neighbor(int i, int j, int type)
{
	for (int a = i - 2; a < i + 2; a++) {
		for (int b = j - 2; b < j + 2; b++) {
			if (inBOX(a, b)) {
				neighbor[a][b] += type;
			}
		}
	}
}
int paritition(seat A[], int low, int high)
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
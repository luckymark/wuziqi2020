#include "func.hpp"
void setColor(int i, int j, int color)
{
	BOX[i][j].color_val = color;
}
// 是否在棋盘中
bool inBOX(int i, int j)
{
	return i >= 0 && j >= 0 && i <= 14 && j <= 14;
}
// 比较大小
// type 'b' : 返回较大的数
// type 's' : 返回较小的数
int compare(int x, int y, bool bigger)
{
	if (bigger)
		return (x > y) ? x : y;
	else
		return (x < y) ? x : y;
}
// 判断当前位置是否为输入的颜色
bool isColor(int i, int j, int color)
{
	return BOX[i][j].color_val == color;
}
// 优化速度函数 
// 判断最近的 5 * 5 的格子中是否有落子 
// 也许需要扩大判断范围
bool have_neighbor55(int i, int j)
{
	int cur_i = i;
	int cur_j = j;
	int pd = false;
	i -= 2;
	j -= 2;
	if (i < 0) i = 0;
	if (j < 0) j = 0;
	for (int a = i; a < cur_i + 2 && a <= 14; a++) {
		for (int b = j; b < cur_j + 2 && b <= 14; b++) {
			if (BOX[a][b].color_val != -1) {
				pd = true;
				goto there;
			}
		}
	}
there:
	return pd;
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
void initStar(seat* star, int i, int j)
{
	int count = 0;
	for (int a = 0; a < 4; a++) {
		for (int b = 1; b <= 5; b++) {
			star[count].i = i + b * di[a];
			star[count++].j = j + b * dj[a];
			star[count].i = i - b * di[a];
			star[count++].j = j - b * dj[a];
		}
	}
}
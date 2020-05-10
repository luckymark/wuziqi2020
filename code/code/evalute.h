#include "define_var.h"

int calc_point(int map[][MAXN]);
int lines_point(int map[][MAXN]);
int rank_point(int map[][MAXN]);
int left_point(int map[][MAXN]);
int right_point(int map[][MAXN]);
int white_black(int white, int black);

int legal(int x, int y);
int calc_part_point(int map[][MAXN], int color, int x, int y);
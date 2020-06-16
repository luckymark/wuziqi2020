#pragma once
#include <stdio.h>

/*struct pos
{
	int pos_x;
	int pos_y;
	int pos_score;
};
pos findbestseat(int chess[15][15], int color, int c);*/

struct pos
{
	int pos_x = 0;
	int pos_y = 0;
};

pos AI(const int chess[15][15], int olds_chess[15][15]);
void CheeseStatistics(const int olds_chess[15][15], int cheese[15][15][8][2]);
void Score(const int status[15][15], int cheese[15][15][8][2], int score1[15][15], int score2[15][15]);//ÆÀ¹Àº¯Êý
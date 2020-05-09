#pragma once
#include "Player.h"
class ChessAI : public Player
{
private:
	long long score_self,score_other;
	int want_set_x, want_set_y;	//在递归出最优解时应该下的位置
	int* guess_line(int x, int y, int front);
public:
	void get_score(Checkerboard& board,int x,int y);//获得在x，y下棋后的棋盘对score的改变

};


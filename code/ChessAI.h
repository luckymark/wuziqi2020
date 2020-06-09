#pragma once
#include "Player.h"
#include <string>

enum RESULT {
	DRAW,
	B_WIN,
	W_WIN
};

struct EVALUATION {
	long long score;
	RESULT result;
	int STAT[8];//用来储存某些棋型，看能不能杀棋

	EVALUATION() : score(0){
		memset(STAT, 0, sizeof(STAT));
	}
};

class ChessAI : public Player
{
private:
	void init_typescore();//初始化棋型
public:
	EVALUATION get_score(Checkerboard& board);

};


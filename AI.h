#pragma once
#include<QPoint>
#include"Score_Config.h"
#include<vector>
#include<ctime>

struct Chess {
	int x;
	int y;
	int score;
	Turns color;
	Chess():x(0),y(0),score(0),color(WHITE){}
};

class AI {
public:
	AI();
	int EvaluateGreedy(int x, int y, Turns);
	void UpdateBoard(int x,int y,Turns t);
	Turns Now_Color() { return role; }
	void ReserveRole();
	Chess& BestChess();
	bool GamingOrNot();
private:
	Chess decision;
	Chess best;
	int game_board[BoardLength][BoardLength];
	int score_board[BoardLength][BoardLength];
	int hum_score_board[BoardLength][BoardLength];
	int ai_score_board[BoardLength][BoardLength];
	std::vector<Chess> same_score_chess;
	bool game_status;
	Turns role;
	int count;
	Edge_Status head, end;		//头部为第一次判断的方向，尾部为第二次判断的方向
	void ResetData();
	int TurnToScore(int cnt, Edge_Status h, Edge_Status e);
	void UpdateScoreGreedy();
	void UpdateScore();
	Turns opponent(Turns t)
	{
		if (t == BLACK)	return WHITE;
		else return BLACK;
	}
	int minimax(int depth, int alpha, int beta, bool maxmizingPlayer);
	bool HasNeighbour(int x, int y);
	void gen(std::vector<Chess>& v,Turns t);
	void sort(std::vector<Chess>& v);
	int Evaluate(Turns t);
};
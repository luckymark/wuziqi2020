#pragma once
#include "Checkerboard.h"
enum color {
	NOTHING,
	BLACKCHESS,
	WHITECHESS
};
enum chessStyle {

};
class Player
{
private:
	int color;
	void catch_mouth(int& x, int& y);
public:
	Player(int _color) : color(_color) {};

	bool player_set_chess(Checkerboard& board);
	bool set_chess(Checkerboard& board, int x, int y);
	int* get_line(Checkerboard& board, int x, int y, int front);
	int judgeChess(int* line);//TODO:³¬³¤ÅÐ¶Ï
};


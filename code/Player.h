#pragma once
#include "Checkerboard.h"

enum color {
	NOTHING,
	BLACKCHESS,
	WHITECHESS
};

class Player
{
private:
	void catch_mouth(int& x, int& y);
public:
	int color;
	Player() :color(NOTHING) {};
	Player(int _color) : color(_color) {};

	bool player_set_chess(Checkerboard& board);
	bool set_chess(Checkerboard& board, int x, int y);
	int* get_line(Checkerboard& board, int x, int y, int front);
};


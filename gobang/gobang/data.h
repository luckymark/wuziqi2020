#pragma once
#define Black 1
#define White 2
#define Empty 0
typedef struct PPoint {
	int x, y;
	int score;
	bool operator < (const PPoint& b)const
	{
		return score > b.score;
	}
}Point;
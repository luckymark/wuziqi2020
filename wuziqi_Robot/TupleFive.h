#pragma once
#include "GameEngine.h"

//struct
typedef struct {
	int x,y,direction;
} TupleFivePoint;


//prototype
TupleScore getScore_FiveTuple(GameEngine engine);
int getTmpTupleScore(GameEngine engine, TupleFivePoint point);
void flushTmpTupleScore(TupleScore* score, TupleFivePoint point, int tmpScore);
int isOutOfTupleStartRange(TupleFivePoint point);

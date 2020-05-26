#pragma once

#include "GameEngine.h"


//struct
typedef struct {
	int x,y,direction;
} TupleScorePoint;

typedef struct {
	int index, value;
} TupleSortingNode;


//prototype
TupleScore getScore_FiveTuple(GameEngine engine);
int getTmpTupleScore(GameEngine engine, TupleScorePoint point);
void flushTmpTupleScore(TupleScore* score, TupleScorePoint point, int tmpScore);
int isOutOfTupleStartRange(TupleScorePoint point);
TuplePriorScore convertToPriorTupleScore(TupleScore score);
int cmpTupleSortingNode(const void* a, const void* b);



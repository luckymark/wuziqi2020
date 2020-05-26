#pragma once
#include <string.h>
#include <stdlib.h>
#include "GameEngine.h"
#include "TupleFive.h"

//struct
typedef struct {
	int alpha, beta, step,value;
} Node_MaxMinSearch;

//prototype
int getBestMove_MaxMinSearch(GameEngine engine);
int maxMinSearch(GameEngine engine, Node_MaxMinSearch node);
TuplePriorScore convertToPriorTupleScore(TupleScore score);
int cmpTupleScore(const void* a, const void* b);
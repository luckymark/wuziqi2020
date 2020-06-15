#pragma once

//struct
typedef struct {
	int alpha, beta, step,value;
} Node_MaxMinSearch;

//prototype
int getBestMove_MaxMinSearch(GameEngine engine);
int maxMinSearch(GameEngine engine, Node_MaxMinSearch node);

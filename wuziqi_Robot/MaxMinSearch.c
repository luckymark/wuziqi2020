#include "MaxMinSearch.h"
#define MAXMIN_DEPTH 6
#define PRIOR_COUNT 10
#define INF 99999999


/*	return the optimized linear 15*15 Gomoku position */
int getBestMove_MaxMinSearch(GameEngine engine)
{
	//init
	TuplePriorScore priorScore = convertToPriorTupleScore(getScore_FiveTuple(engine));
	Node_MaxMinSearch startNode = {.alpha = -INF,.beta = INF,.step = 0,.value = 0};
	int i,x,y,result = priorScore.list[0],maxEvaluation = 0,tmpEvaluation;

	for (i = 0; i < PRIOR_COUNT; i++)
	{
		//init
		x = priorScore.list[i] / 15;
		y = priorScore.list[i] % 15;
		if (PLAYER_BLACK == engine.playerColor)
			engine.squareMap.map[x][y] = CHESS_BLACK;
		else
			engine.squareMap.map[x][y] = CHESS_WHITE;

		//max min search
		tmpEvaluation = maxMinSearch(engine, startNode);
		engine.squareMap.map[x][y] = CHESS_EMPTY;

		//update max evaluation and relevant position
		if (tmpEvaluation > maxEvaluation)
		{
			result = priorScore.list[i];
			maxEvaluation = tmpEvaluation;
		}
	}

	return result;
}

int maxMinSearch(GameEngine engine, Node_MaxMinSearch node)
{
	//short circuit
	if (node.step >= MAXMIN_DEPTH)
	{
		int result = 0;
		result = getMapEvaluation(engine);
		return result;
	}

	//init
	TupleScore tmpScore = getScore_FiveTuple(engine);
	TuplePriorScore tmpPrScore = convertToPriorTupleScore(tmpScore);
	int i,x,y,result;
	Node_MaxMinSearch nextNode;
	GameEngine tmpEngine;

	//dfs loop
	for (i = 0; i < PRIOR_COUNT; i++)
	{
		//init
		tmpEngine = engine;
		x = tmpPrScore.list[i] / 15;
		y = tmpPrScore.list[i] % 15;
		if((PLAYER_BLACK == tmpEngine.playerColor && 0 == node.step % 2) || (PLAYER_WHITE == tmpEngine.playerColor && 1 == node.step % 2))
			tmpEngine.squareMap.map[x][y] = CHESS_BLACK;
		else
			tmpEngine.squareMap.map[x][y] = CHESS_WHITE;
		nextNode = node;

		//alpha beta prune
		if (nextNode.alpha >= nextNode.beta)
			break;
		nextNode.step++;

		//search next layer
		result = maxMinSearch(tmpEngine, nextNode);

		//update node
		if (1 == node.step % 2)   //MIN layer	
			node.value = (node.beta = (result < node.beta ? result : node.beta));		
		else   //MAX layer		
			node.value = (node.alpha = (result > node.alpha ? result : node.alpha));			
		
	}

	return node.value;
}

TuplePriorScore convertToPriorTupleScore(TupleScore score)
{
	
}

int cmpTupleScore(const void* a, const void* b)
{

}
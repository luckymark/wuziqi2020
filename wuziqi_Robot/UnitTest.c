#include "pch.h"
#include "GameEngine.h"
#include "TupleFive.h"
#include "MaxMinSearch.h"
#include "GlobalEvaluation.h"

int testTupleFive()
{
	//isOutOfTupleStartRange
	if (0 == isOutOfTupleStartRange((TupleScorePoint) { -1, -1, 0 }))
		return 1;
	if (0 == isOutOfTupleStartRange((TupleScorePoint) { 1, 11, 0 }))
		return 1;
	if (0 == isOutOfTupleStartRange((TupleScorePoint) { 11, 1, 1 }))
		return 1;
	if (0 == isOutOfTupleStartRange((TupleScorePoint) { 12, 1, 2 }))
		return 1;
	if (0 == isOutOfTupleStartRange((TupleScorePoint) { 1, 1, 3 }))
		return 1;

	//flushTmpTupleScore
	TupleScore score = { 0 };
	flushTmpTupleScore(&score, (TupleScorePoint) { 0, 0, 2 }, 123);
	int i;
	for (i = 0; i < 5; i++)
	{
		if (123 != score.map[i][i])
			return 2;
	}

	//getTmpTupleScore
	GameEngine engine;
	memset(&engine, 0, sizeof(GameEngine));
	engine.playerColor = PLAYER_BLACK;
	for (i = 0; i < 4; i++)
	{
		engine.squareMap.map[i][i] = CHESS_BLACK;
	}
	if (800000 != getTmpTupleScore(engine, (TupleScorePoint) { 0, 0, 2 }))
		return 3;
	engine.squareMap.map[4][4] = CHESS_WHITE;
	if (0 != getTmpTupleScore(engine, (TupleScorePoint) { 0, 0, 2 }))
		return 3;

	//convertToPriorTupleScore
	for (i = 0; i < 5; i++)
		score.map[i][i] += i;
	TuplePriorScore prScore = convertToPriorTupleScore(score);
	for (i = 0; i < 4; i++)
	{
		if (16 * (4 - i) != prScore.list[i])
			return 4;
	}

	//getScoreFiveTuple
	engine.squareMap.map[4][4] = CHESS_EMPTY;
	score = getScoreFiveTuple(engine);
	prScore = convertToPriorTupleScore(score);
	if (64 != prScore.list[0])
		return 5;

	return 0;
}

int testGlobalEvaluation()
{
	//getGE_IntX
	int line_A[15] = {0};
	if (0 != getGE_IntX(line_A,15, PLAYER_BLACK))
		return 1;
	int line_B[15] = { 0,0,0,1,0,0,0,1,0,1,1,1,1,0,0 };
	if (6830 != getGE_IntX(line_B,15, PLAYER_BLACK))
		return 1;

	//getHorizontalGE
	GameEngine engine;
	memset(&engine, 0, sizeof(engine));
	engine.playerColor = PLAYER_BLACK;
	int i, j;
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
			engine.squareMap.map[i][j] = line_B[j];
	if (6830 * 15 != getHorizontalGE(engine))
		return 2;

	//getVerticalGE
	for (j = 0; j < 15; j++)
		for (i = 0; i < 15; i++)
			engine.squareMap.map[i][j] = line_B[i];
	if (60000 != getHorizontalGE(engine))
		return 3;

	//getObliqueGE_A
	//return getObliqueGE_A(engine) - 20;

	//getObliqueGE_B
	//return getObliqueGE_B(engine) - 20;

	//getGlobalEvaluation
	//return getGlobalEvaluation(engine) - 20;

	return 0;
}

int testMaxMinSearch()
{
	return 0;
}
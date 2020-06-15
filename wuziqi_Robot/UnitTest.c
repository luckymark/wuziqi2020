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
	if (0 == isOutOfTupleStartRange((TupleScorePoint) { 11, 1, 0 }))
		return 1;
	if (0 == isOutOfTupleStartRange((TupleScorePoint) { 1, 11, 1 }))
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
	for (i = 0; i < 5; i++)
	{
		if (16 * i != prScore.list[i])
			return 10*i+4;
	}

	//getScore_FiveTuple
	engine.squareMap.map[5][5] = CHESS_EMPTY;
	score = getScoreFiveTuple(engine);
	prScore = convertToPriorTupleScore(score);
	if (64 != prScore.list[i])
		return 5;

	return 0;
}
#include "pch.h"
#include "GameEngine.h"
#include "TupleFive.h"

//const
TupleScorePoint nextStep[4] = {
	{0,1,0},
	{1,0,0},
	{1,1,0},
	{1,-1,0}
};
int scoreMyColor[5] = {0,35,800,15000,800000};
int scoreEnemyColor[5] = {0,15,400,1800,100000};

//function
TupleScore getScoreFiveTuple(GameEngine engine)
{
	//init
	TupleScore result = {0};
	int i, j,x,y,direction;
	TupleScorePoint tmpPoint = {0,0,0};
	int tmpScore = 0;

	//calculate score
	for(direction = 0;direction < 4;direction++)
		for(x = 0;x < 15; x++)
			for (y = 0; y < 15; y++)
			{
				tmpPoint = (TupleScorePoint){ x,y,direction };
				if (1 == isOutOfTupleStartRange(tmpPoint))
					continue;
				tmpScore = getTmpTupleScore(engine, tmpPoint);
				flushTmpTupleScore(&result, tmpPoint, tmpScore);
			}

	//if placed with chess, set score to -1
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
			if (CHESS_EMPTY != engine.squareMap.map[i][j])
				result.map[i][j] = -1;

	return result;
}

int getTmpTupleScore(GameEngine engine, TupleScorePoint point)
{	
	//init
	int b = 0, w = 0;

	//get num of black and white in a tuple
	for (int i = 1; i <= 5; i++)
	{
		if (CHESS_BLACK == engine.squareMap.map[point.x][point.y])
			b++;
		if (CHESS_WHITE == engine.squareMap.map[point.x][point.y])
			w++;
		point = pointPlus(point, nextStep[point.direction]);
	}

	//case polluted
	if (0 != b * w)
		return 0;

	//case blank
	if (0 == b + w)
		return 7;

	if (PLAYER_BLACK == engine.playerColor)
		return (scoreMyColor[b] > scoreEnemyColor[w] ? scoreMyColor[b] : scoreEnemyColor[w]);
	else
		return (scoreMyColor[w] > scoreEnemyColor[b] ? scoreMyColor[w] : scoreEnemyColor[b]);
}

void flushTmpTupleScore(TupleScore* score, TupleScorePoint point, int tmpScore)
{
	TupleScorePoint tmp = point;
	for (int i = 1; i <= 5; i++)
	{
		score->map[tmp.x][tmp.y] += tmpScore;
		tmp = pointPlus(tmp, nextStep[point.direction]);
	}
}

int isOutOfTupleStartRange(TupleScorePoint point)
{
	if (point.x < 0 || point.x > 14 || point.y < 0 || point.y > 14)
		return 1;
	switch (point.direction)
	{
	case 0:   //horizontal
		if (point.y > 10)
			return 1;
		break;
	case 1:   //vertical
		if (point.x > 10)
			return 1;
		break;
	case 2:   //oblique 00 to nn
		if (point.x > 10 || point.y > 10)
			return 1;
		break;
	case 3:   //oblique 0n to n0
		if (point.x > 10 || point.y < 4)
			return 1;
		break;
	default:
		break;
	}

	return 0;
}

TupleScorePoint pointPlus(TupleScorePoint a, TupleScorePoint b)
{
	return (TupleScorePoint) { a.x + b.x, a.y + b.y, (a.direction + b.direction) % 4 };
}

TuplePriorScore convertToPriorTupleScore(TupleScore score)
{
	//init
	int i, j;
	TuplePriorScore result;
	TupleSortingNode nodeList[225];
	memset(&nodeList, 0, sizeof(TupleSortingNode) * 225);

	//create nodeList
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
		{
			nodeList[15 * i + j].index = 15 * i + j;
			nodeList[15 * i + j].value = score.map[i][j];
		}

	//qsort
	qsort(nodeList, 225, sizeof(TupleSortingNode), cmpTupleSortingNode);

	//convert to int array
	for (i = 0; i < 225; i++)
		result.list[i] = nodeList[i].index;

	return result;
}

int cmpTupleSortingNode(const void* a, const void* b)
{
	TupleSortingNode* c = (TupleSortingNode*)a;
	TupleSortingNode* d = (TupleSortingNode*)b;
	return d->value - c->value;
}


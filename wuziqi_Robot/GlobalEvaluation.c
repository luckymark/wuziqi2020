#include "GlobalEvaluation.h"
#include "GEInt15Data_Black.h"
#include "pch.h"

int getGlobalEvaluation(GameEngine engine)
{
	//init
	int i, j, direction,line[15], result = 0;

	result += getHorizontalGE(engine);
	result += getVerticalGE(engine);
	result += getObliqueGE_A(engine);
	result += getObliqueGE_B(engine);

	return result;
}

int getHorizontalGE(GameEngine engine)
{
	int i, j, line[15], result = 0;
	memset(&line, 0, sizeof(int) * 15);
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			line[j] = engine.squareMap.map[i][j];
		}
		result += getOneLine_GE_Score(line, engine.playerColor);
	}
	return result;
}

int getVerticalGE(GameEngine engine)
{
	int i, j, line[15], result = 0;
	memset(&line, 0, sizeof(int) * 15);
	for (j = 0; j < 15; j++)
	{
		for (i = 0; i < 15; i++)
		{
			line[i] = engine.squareMap.map[i][j];
		}
		result += getOneLine_GE_Score(line, engine.playerColor);
	}
	return result;
}

int getObliqueGE_A(GameEngine engine)
{
	int start = 10, step = 5,p,line[15],result = 0;
	memset(&line, 0, sizeof(int) * 15);
	for (start = 10; start > 0; start--)
	{
		for (p = 0; p < step; p++)
		{
			line[p] = engine.squareMap.map[p][start + p];
		}
		result += getOneLine_GE_Score(line, engine.playerColor);
		for (p = 0; p < step; p++)
		{
			line[p] = engine.squareMap.map[start + p][p];
		}
		result += getOneLine_GE_Score(line, engine.playerColor);
		step++;
	}
	for (p = 0; p < 15; p++)
	{
		line[p] = engine.squareMap.map[p][p];
	}
	result += getOneLine_GE_Score(line,engine.playerColor);

	return result;
}

int getObliqueGE_B(GameEngine engine)
{
	int start = 10, step = 5, p, line[15], result = 0;
	memset(&line, 0, sizeof(int) * 15);
	for (start = 5; start < 14; start++)
	{
		for (p = 0; p < step; p++)
		{
			line[p] = engine.squareMap.map[p][start - p];
		}
		result += getOneLine_GE_Score(line, engine.playerColor);
		for (p = 0; p < step; p++)
		{
			line[p] = engine.squareMap.map[start - p][p];
		}
		result += getOneLine_GE_Score(line, engine.playerColor);
		step++;
	}
	for (p = 0; p < 15; p++)
	{
		line[p] = engine.squareMap.map[p][14-p];
	}
	result += getOneLine_GE_Score(line,engine.playerColor);

	return result;
}

int getOneLine_GE_Score(int line[15], int playerColor)
{
	int i,j = 1,index = 0,result;
	
	for (i = 14; i >=0; i--)
	{
		index += line[i] * j;
		j *= 3;
	}

	result = GEInt15_Data_Black[index];
	if (PLAYER_WHITE == playerColor)
		result = -result;
	return result;
}
#include "pch.h"
#include "GlobalEvaluation.h"

extern short GEInt5_Data_Black[243];
extern short GEInt6_Data_Black[729];
extern short GEInt7_Data_Black[2187];
extern short GEInt8_Data_Black[6561];
extern short GEInt9_Data_Black[19683];
extern short GEInt10_Data_Black[59049];
extern short GEInt11_Data_Black[177147];
extern short GEInt12_Data_Black[531441];
extern short GEInt13_Data_Black[1594323];
extern short GEInt14_Data_Black[4782969];
extern short GEInt15_Data_Black[14348907];

int getGlobalEvaluation(GameEngine engine)
{
	//init
	int result = 0;

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
		result += getGE_IntX(line,15, engine.playerColor);
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
		result += getGE_IntX(line, 15, engine.playerColor);
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
		result += getGE_IntX(line, step, engine.playerColor);
		for (p = 0; p < step; p++)
		{
			line[p] = engine.squareMap.map[start + p][p];
		}
		result += getGE_IntX(line, step, engine.playerColor);
		step++;
	}
	for (p = 0; p < 15; p++)
	{
		line[p] = engine.squareMap.map[p][p];
	}
	result += getGE_IntX(line, 15, engine.playerColor);

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
		result += getGE_IntX(line, step, engine.playerColor);
		for (p = 0; p < step; p++)
		{
			line[p] = engine.squareMap.map[14 - start + p][14 - p];
		}
		result += getGE_IntX(line, step, engine.playerColor);
		step++;
	}
	for (p = 0; p < 15; p++)
	{
		line[p] = engine.squareMap.map[p][14-p];
	}
	result += getGE_IntX(line, 15, engine.playerColor);

	return result;
}

int getLineIndex(int line[15], int count)
{
	int i, j = 1, index = 0;

	for (i = count - 1; i >= 0; i--)
	{
		index += line[i] * j;
		j *= 3;
	}

	return index;
}

int getGE_IntX(int line[15],int x, int playerColor)
{
	int index, result;

	index = getLineIndex(line, x);

	switch (x)
	{
	case 5:
		result = GEInt5_Data_Black[index];
		break;
	case 6:
		result = GEInt6_Data_Black[index];
		break;
	case 7:
		result = GEInt7_Data_Black[index];
		break;
	case 8:
		result = GEInt8_Data_Black[index];
		break;
	case 9:
		result = GEInt9_Data_Black[index];
		break;
	case 10:
		result = GEInt10_Data_Black[index];
		break;
	case 11:
		result = GEInt11_Data_Black[index];
		break;
	case 12:
		result = GEInt12_Data_Black[index];
		break;
	case 13:
		result = GEInt13_Data_Black[index];
		break;
	case 14:
		result = GEInt14_Data_Black[index];
		break;
	case 15:
		result = GEInt15_Data_Black[index];
		break;
	default:
		result = 0;
		break;
	}

	if (PLAYER_WHITE == playerColor)
		result = -result;
	return result;
}

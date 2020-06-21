#include "pch.h"
#include "check.h"
#include <string.h>

extern short JudgeData[14348907];

int checkHorizental(int map[225])
{
	int i, j, line[15], result = 0;
	memset(&line, 0, sizeof(int) * 15);
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			line[j] = map[15 * i + j];
		}
		result = checkLine(line);
		if (result)
			return result;
	}
	return 0;
}

int checkVertical(int map[225])
{
	int i, j, line[15], result = 0;
	memset(&line, 0, sizeof(int) * 15);
	for (j = 0; j < 15; j++)
	{
		for (i = 0; i < 15; i++)
		{
			line[j] = map[15 * i + j];
		}
		result = checkLine(line);
		if (result)
			return result;
	}
	return 0;
}

int checkObliqueA(int map[225])
{
	int start = 10, step = 5, p, line[15], result = 0;
	memset(&line, 0, sizeof(int) * 15);
	for (start = 10; start > 0; start--)
	{
		for (p = 0; p < step; p++)
		{
			line[p] = map[start + 16*p];
		}
		result = checkLine(line);
		if (result)
			return result;
		for (p = 0; p < step; p++)
		{
			line[p] = map[15 * start +16 *  p];
		}
		result = checkLine(line);
		if (result)
			return result;
		step++;
	}
	for (p = 0; p < 15; p++)
	{
		line[p] = map[16 * p];
	}
	result = checkLine(line);
	if (result)
		return result;

	return 0;
	
}

int checkObliqueB(int map[225])
{
	int start = 10, step = 5, p, line[15], result = 0;
	memset(&line, 0, sizeof(int) * 15);
	for (start = 5; start < 14; start++)
	{
		for (p = 0; p < step; p++)
		{
			line[p] = map[15 * p + start - p];
		}
		result = checkLine(line);
		if (result)
			return result;
		for (p = 0; p < step; p++)
		{
			line[p] = map[15 * (start - p) + p];
		}
		result = checkLine(line);
		if (result)
			return result;
		step++;
	}
	for (p = 0; p < 15; p++)
	{
		line[p] = map[15 * p + 14 - p];
	}
	result = checkLine(line);
	if (result)
		return result;

	return 0;
}

int checkLine(int line[15])
{
	int i, j = 1, index = 0;

	for (i = 14; i >= 0; i--)
	{
		index += line[i] * j;
		j *= 3;
	}

	return JudgeData[index];
}

int isDraw(int map[225])
{
	int i;
	for (i = 0; i < 225; i++)
		if (0 == map[i])
			return 0;

	return 3;
}


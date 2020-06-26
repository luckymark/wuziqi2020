#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char symbol[3] = { 'O','#','*' };

int checkObliqueA(int map[225]);
void showLine(int line[15]);
void showMap(int map[225]);

int main()
{
	int map[225] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	printf("this is the map:\n");
	showMap(map);
	printf("\n\n\n");

	//checkVertical(map);

	checkObliqueB(map);

	system("pause");
}

int checkVertical(int map[225])
{
	int i, j, line[15], result = 0;
	memset(&line, 0, sizeof(int) * 15);
	for (j = 0; j < 15; j++)
	{
		for (i = 0; i < 15; i++)
		{
			//printf("line[%i] = map[%d] = %c\n",i,15*i+j,symbol[map[15*i+j]]);
			line[i] = map[15 * i + j];
		}
		showLine(line);
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
			line[p] = map[start + 16 * p];
		}
		showLine(line);
		for (p = 0; p < step; p++)
		{
			line[p] = map[15 * start + 16 * p];
		}
		showLine(line);
		step++;
	}
	for (p = 0; p < 15; p++)
	{
		line[p] = map[16 * p];
	}
	showLine(line);

	return 0;

}

int checkObliqueB(int map[225])
{
	int start = 10, step = 5, p, line[15], result = 0;
	memset(&line, 0, sizeof(int) * 15);
	for (start = 4; start < 14; start++)
	{
		for (p = 0; p < step; p++)
		{
			line[p] = map[15 * p + start - p];
		}
		showLine(line);
		for (p = 0; p < step; p++)
		{
			line[p] = map[15 * (14 - start + p) + 14 - p];
		}
		showLine(line);
		step++;
	}
	for (p = 0; p < 15; p++)
	{
		line[p] = map[15 * p + 14 - p];
	}
	showLine(line);

	return 0;
}



void showLine(int line[15])
{
	for (int i = 0; i < 15; i++)
		printf(" %c ", symbol[line[i]]);
	printf("\n\n");
}

void showMap(int map[225])
{
	for (int i = 0; i < 225; i++)
	{
		if (0 == i % 15)
			printf("\n\n");
		printf(" %c ", symbol[map[i]]);
	}
}

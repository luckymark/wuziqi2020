#include"gobangAI.h"
#include"game.h"
#include"view.h"

//сно╥й╓юШеп╤о
int gamewin() {
	for (int i = 0; i < CbIntNum; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if ((BoardKey[i][j] == P_BLACK) && (BoardKey[i][j + 1] == P_BLACK) && (BoardKey[i][j + 2] == P_BLACK) && (BoardKey[i][j + 3] == P_BLACK) && (BoardKey[i][j + 4] == P_BLACK))
			{
				return 1;
			}
			if ((BoardKey[i][j] == P_WHITE) && (BoardKey[i][j + 1] == P_WHITE) && (BoardKey[i][j + 2] == P_WHITE) && (BoardKey[i][j + 3] == P_WHITE) && (BoardKey[i][j + 4] == P_WHITE))
			{
				return 2;
			}
			if ((BoardKey[j][i] == P_BLACK) && (BoardKey[j + 1][i] == P_BLACK) && (BoardKey[j + 2][i] == P_BLACK) && (BoardKey[j + 3][i] == P_BLACK) && (BoardKey[j + 4][i] == P_BLACK))
			{
				return 1;
			}
			if ((BoardKey[j][i] == P_WHITE) && (BoardKey[j + 1][i] == P_WHITE) && (BoardKey[j + 2][i] == P_WHITE) && (BoardKey[j + 3][i] == P_WHITE) && (BoardKey[j + 4][i] == P_WHITE))
			{
				return 2;
			}

		}
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if ((BoardKey[i][j] == P_BLACK) && (BoardKey[i + 1][j + 1] == P_BLACK) && (BoardKey[i + 2][j + 2] == P_BLACK) && (BoardKey[i + 3][j + 3] == P_BLACK) && (BoardKey[i + 4][j + 4] == P_BLACK))
			{
				return 1;
			}
			if ((BoardKey[i][j] == P_WHITE) && (BoardKey[i + 1][j + 1] == P_WHITE) && (BoardKey[i + 2][j + 2] == P_WHITE) && (BoardKey[i + 3][j + 3] == P_WHITE) && (BoardKey[i + 4][j + 4] == P_WHITE))
			{
				return 2;
			}
			if ((BoardKey[i + 4][j] == P_BLACK) && (BoardKey[i + 3][j + 1] == P_BLACK) && (BoardKey[i + 2][j + 2] == P_BLACK) && (BoardKey[i + 1][j + 3] == P_BLACK) && (BoardKey[i][j + 4] == P_BLACK))
			{
				return 1;
			}
			if ((BoardKey[i + 4][j] == P_WHITE) && (BoardKey[i + 3][j + 1] == P_WHITE) && (BoardKey[i + 2][j + 2] == P_WHITE) && (BoardKey[i + 1][j + 3] == P_WHITE) && (BoardKey[i][j + 4] == P_WHITE))
			{
				return 2;
			}
		}
	}
	return 0;
}
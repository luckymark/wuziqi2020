#pragma once

typedef struct current
{
	int x;
	int y;
}CURRENT;

#define sp "                              "
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
#define PINF 2147483647		// 正无穷,Beta
#define NINF -2147483648	// 负无穷,Alpha
#define DEPTH 4				// 搜索深度


bool win(int x,int y,int map[16][16]);
bool judge(int x, int y,int map[16][16]);
void putmap(void);
void playchess(void);
void computerchess(void);
int score(int a, int map[16][16], int n);
int maxmin(int map[16][16], int deep, int Alpha, int Beta);
int judge2(int i, int j, int map[16][16],int n);
bool four(int x, int y, int map[16][16]);
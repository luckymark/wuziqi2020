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
void oblique4(int  map[16][16], int a, int& sum);
void oblique3(int  map[16][16], int a, int& sum);
void oblique2(int  map[16][16], int a, int& sum);
void oblique1(int  map[16][16], int a, int& sum);
void rowscore(int  map[16][16], int a, int& sum);
void linescore(int  map[16][16], int a, int& sum);
void Liveone(int  map[16][16], int a, int& sum);
int maxmin(int map[16][16], int deep, int Alpha, int Beta);
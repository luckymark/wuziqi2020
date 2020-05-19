

#pragma once

#define LENGHT 640
#define WEIGHT 640
#define LINE 16
#define EACH 40

#define MAXN 17

;

extern int dis(int x, int y, int x1, int y1);
extern void input_black(int map[][MAXN]);
extern void initboard();
extern void Print_White(int x, int y);
extern void Pushboard();

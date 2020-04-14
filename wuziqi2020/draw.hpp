#ifndef __DRAW__
#define __DRAW__


#include <conio.h>
#include <graphics.h>

// 类定义

// 保存位置的类
class seat
{
public:
	int i = 0;      // y 坐标
	int j = 0;      // x 坐标
	int score = INT_MIN;  // 分数
};

// 保存棋盘的类
class box
{
public:
	void draw();            // 绘制
public:
	int x = 0;              // x 坐标
	int y = 0;              // y 坐标
	int color_val = -1;     // 值（黑棋：1，白棋：0，空位：-1）
	int modle;              // 模式
	bool isnew = false;     // 是否有选择框
	int score = 0;          // 分数
	COLORREF color = WHITE; // 棋盘背景色
};


// 函数声明
void draw();                  // 绘制
void init();                  // 初始化
seat findbestseat1(int);	  // 寻找最佳位置
void isWIN();                 // 判断输赢
void game();                  // 游戏主函数

#endif // !__DRAW__



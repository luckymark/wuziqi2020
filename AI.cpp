//#include<stdio.h>
//#include<stdlib.h>
//#define length 4
//
//typedef  struct record {
//	int x,y;
//	int mark[15][15];
//	struct record* next;
//}record;
//
////int Bscore[15][15][4][length];
//void evaluate(const int V[15][15],int mark/*,int *s*/);
//
////void score(int V[15][15], int*s);
//
//
///*对棋盘空位进行打分，选择AI落子的最佳空位*/
//void AI(const int status[15][15], /*nt olds[15][15],*/ int* set)
//{
//	int i,j,l;
//	//int s[2];
//	//int V[17][17] = {3};
//	//for (i = 1; i <= 15; i++) {
//	//	for (j = 1; j <= 15; j++) { 
//	//		V[i][j] = status[i-1][j-1];
//	//	}
//	//}
//	int V[15][15];
//	for (i = 0; i < 15; i++) {
//	    for (j = 0; j < 15; j++) {
//		     V[i][j] = status[i][j];
//	    }
//    }
//	record* header=NULL;
//	record* p = (record*)malloc(sizeof(record));
//	p->next = NULL;
//	header = p;
//	//score(V, set);
//}
//
//
//
///*判断当前局势的分数*/
//void evaluate(const int V[15][15],record* m/*,int *s*/)
//{
//	int i, j, k, t, count, n, score/*,*//* score1[15][15],score2[15][15]*//*,max*/;
//	int tx, ty;
//	int drtx[8] = { 0,1,1,1,0,-1,-1,-1 };//代表某一点向8个方向的坐标位移量
//	int drty[8] = { -1,-1,0,1,1,1,0,-1 };//数组元素中0号为“上”然后沿顺时针依次增加
//	//int score1[15][15][(length / 2)];
//	//int score2[15][15][(length / 2)];
//	//int bx, by, wx, wy;
//	int cheese[15][15][8][2];
//	//max = 0;
//	//eval* header=NULL;
//	//eval* p = (eval*)malloc(sizeof(eval));
//	//p->next = NULL;
//	//header = p;
//
//	//for (n = 1; n < length; n++) {
//		if (n % 2 != 0) {
//			for (i = 0; i <= 14; i++) {         //行
//				for (j = 0; j <= 14; j++) {     //列
//					if (V[i][j] == 0)//判断该位置是否有棋子
//					{
//						for (k = 0; k < 8; k++)
//						{
//							count = 0;
//							tx = i; ty = j;
//							for (t = 0; t < 5; t++)//最多判断五个连子
//							{
//								tx += drtx[k];
//								ty += drty[k];
//								if (tx > 15 || tx < 1 || ty > 15 || ty < 1)//限制在棋盘内
//									break;
//								if (V[tx][ty] == 1)//计算某一方向黑棋个数
//									count++;
//								else
//									break;   //判断是否为连续同一颜色棋子，不同则退出统计
//							}
//							cheese[i][j][k][0] = count;
//						}
//					}
//				}
//			}
//			for (i = 0; i <= 14; i++) {         //行
//				for (j = 0; j <= 14; j++)     //列
//				{
//					if (V[i][j] == 0)
//					{
//						score = 0;
//						for (k = 0; k < 4; k++)
//						{
//							if (cheese[i][j][k][0] + cheese[i][j][k + 4][0] >= 4)
//								score += 10000;
//							else if (cheese[i][j][k][0] + cheese[i][j][k + 4][0] == 3)
//								score += 1000;
//							else if (cheese[i][j][k][0] + cheese[i][j][k + 4][0] == 2)
//								score += 100;
//							else if (cheese[i][j][k][0] + cheese[i][j][k + 4][0] == 1)
//								score += 10;
//						}
//						m->mark[i][j] = score;
//						//if (max < score) {
//						//	tx = i;
//						//	ty = j;
//						//	max = score;
//						//}
///*						p->Rscore[i][j] = score; */          //当前空位对黑棋的分数
//					}
//				}
//			}
//			//return max;
//			//s[0] = tx;
//			//s[1] = ty;
//			//return score;
//		}else {
//			for (i = 0; i <= 14; i++) {         //行
//				for (j = 0; j <= 14; j++) {     //列
//					if (V[i][j] == 0)//判断该位置是否有棋子
//					{
//						for (k = 0; k < 8; k++)
//						{
//							count = 0;
//							tx = i; ty = j;
//							for (t = 0; t < 5; t++)
//				            {
//								tx += drtx[k];
//								ty += drty[k];
//								if (tx > 15 || tx < 1 || ty > 15 || ty < 1)
//									break;
//								if (V[tx][ty] == 2)//判断白棋个数
//									count++;
//								else
//									break;
//							}
//							cheese[i][j][k][1] = count;
//						}
//					}
//				}
//			}
//
//			for (i = 0; i <= 14; i++) {         //行
//				for (j = 0; j <= 14; j++)     //列
//				{
//					if (V[i][j] == 0)
//					{
//						score = 0;
//						for (k = 0; k < 4; k++)
//						{
//							if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] >= 4)
//								score += 10000;
//							else if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] == 3)
//								score += 1000;
//							else if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] == 2)
//								score += 100;
//							else if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] == 1)
//								score += 10;
//						}
///*						p->Rscore[i][j] = score;      */    //当前位置对白棋的分数
//						m->mark[i][j] = score;
//					}
//				}
//			}
//			//s[0] = tx;
//			//s[1] = ty;
//			//return score;
//		}
//		//p->next = (eval*)malloc(sizeof(eval));
//		//p = p->next;
//		//p->next = NULL;
//	//}
//}
//
//
//int simulate(int V[15][15], int len, /*int* set,*/record*p) 
//{
//    int max;
//	//int mark[15][15];
//	int i, j;
//	if (len != 0) {
//		if (len == 6||4||2) {
//			for (i = 0; i < 15; i++) {
//				for (j = 0; j < 15; j++) {
//					if (V[i][j] == 0) {
//						V[i][j] = 2;
//						/*				max=max+*/simulate(V, len - 1/*, set*/, p);
//						p->mark[i][j] = /*max*/simulate(V, len - 1/*, set*/, p);
//						V[i][j] = 0;
//						p->next = (record*)malloc(sizeof(record));
//						p = p->next;
//						p->next = NULL;
//					}
//					//set[0] = i;
//					//set[1] = j;
//				}
//			}
//			for (i = 0; i < 15; i++) {
//				for (j = 0; j < 15; j++) {
//					if (p->mark[i][j] > max) {
//						max = p->mark[i][j];
//						//set[0] = i;
//						//set[1] = j;
//						p->x = i;
//						p->y = j;
//					}
//				}
//			}
//			V[i][j] = 2;
//			evaluate(V, p);
//			//V[i][j] = 0;
//			return max;
//		}else {
//			for (i = 0; i < 15; i++) {
//				for (j = 0; j < 15; j++) {
//					if (V[i][j] == 0) {
//						//p->next = (record*)malloc(sizeof(record));
//						//p = p->next;
//						//p->next = NULL;
//						V[i][j] = 1;
//						/*max=max+*/simulate(V, len - 1/*, set*/, p);
//						p->mark[i][j] = /*max*/simulate(V, len - 1/*, set*/, p);
//						V[i][j] = 0;
//					}
//					//set[0] = i;
//					//set[1] = j;
//				}
//			}
//			for (i = 0; i < 15; i++) {
//				for (j = 0; j < 15; j++) {
//					if (p->mark[i][j] > max) {
//						max = p->mark[i][j];
//						//set[0] = i;
//						//set[1] = j;
//						p->x = i;
//						p->y = j;
//					}
//				}
//			}
//			V[i][j] = 1;
//			evaluate(V, p);
//			//V[i][j] = 0;
//			return max;
//		}
//	}
//	else {
//		max == INT_MIN;
//		evaluate(V, p);
//		for (i = 0; i < 15; i++) {
//			for (j = 0; j < 15; j++) {
//				if (p->mark[i][j] > max) {
//					max = p-> mark[i][j];
//					//set[0] = i;
//					//set[1] = j;
//					p->x = i;
//					p->y = j;
//				}
//			}
//		}
//		return max;
//	}
//}

//void score(int V[15][15], int* s)
//{
//	int j, k, color;
//	int n1, n2;  //计数器，用于累计棋子个数
//	int alterx[length];
//	int altery[length];
//	int socre
//		//for (n = 1; n = length; n++) {
//
//
//		//	if (i % 2 == 0)      //根据计数器i的奇偶性，切换黑棋和白棋的检查
//		//		color = 2;
//		//	else
//		//		color = 1;
//
//		//	while (1)
//		//	{
//		//		n1 = 0;
//		//		n2 = 0;
//		//		for (j = x, k = y; j >= 0; j--)                      //向左检查
//		//		{
//		//			if (status[j][k] == color)                     //判断是否为黑子
//		//				n1++;
//		//			else
//		//				break;
//		//		}
//		//		for (j = x, k = y; j < 15; j++)                            //向右检查
//		//		{
//		//			if (status[j][k] == color)
//		//				n2++;
//		//			else
//		//				break;
//		//		}
//		//		if (n1 + n2 - 1 >= 5)
//		//		{
//		//			return(1);
//		//		}
//		//		n1 = 0;
//		//		n2 = 0;
//		//		for (j = x, k = y; k >= 0; k--)                                //向上检查
//		//		{
//		//			if (status[j][k] == color)
//		//				n1++;
//		//			else
//		//				break;
//		//		}
//		//		for (j = x, k = y; k < 15; k++)                               //向下检查
//		//		{
//		//			if (status[j][k] == color)
//		//				n2++;
//		//			else
//		//				break;
//		//		}
//		//		if (n1 + n2 - 1 >= 5)
//		//		{
//		//			return(1);
//		//		}
//		//		n1 = 0;
//		//		n2 = 0;
//		//		for (j = x, k = y; (j >= 0) && (k >= 0); j--, k--)                    //向左上检查
//		//		{
//		//			if (status[j][k] == color)
//		//				n1++;
//		//			else
//		//				break;
//		//		}
//		//		for (j = x, k = y; (j < 15) && (k < 15); j++, k++)                      //向右下检查
//		//		{
//		//			if (status[j][k] == color)
//		//				n2++;
//		//			else
//		//				break;
//		//		}
//		//		if (n1 + n2 - 1 >= 5)
//		//		{
//		//			return(1);
//		//		}
//		//		n1 = 0;
//		//		n2 = 0;
//		//		for (j = x, k = y; (j < 15) && (k >= 0); j++, k--)                    //向右上检查
//		//		{
//		//			if (status[j][k] == color)
//		//				n1++;
//		//			else
//		//				break;
//		//		}
//		//		for (j = x, k = y; (j >= 0) && (k < 15); j--, k++)                       //向左下检查
//		//		{
//		//			if (status[j][k] == color)
//		//				n2++;
//		//			else
//		//				break;
//		//		}
//		//		if (n1 + n2 - 1 >= 5)
//		//		{
//		//			return(1);
//		//		}
//		//		//return(0);
//		////	}
//		//}
//}



#include<stdio.h>
#include<stdlib.h>
#define length 3

typedef  struct record {
	//int x, y;
	int mark[15][15] = { 0 };
	struct record* next=NULL;
}record;

//int Bscore[15][15][4][length];
void evaluate(const int V[15][15], record* m, int n/*int mark*//*,int *s*/);

int simulate(int V[15][15], int len, /*int* set,*/record* p,int *s);

//void score(int V[15][15], int*s);

int V[15][15];
int drtx[8] = { 0,1,1,1,0,-1,-1,-1 };//代表某一点向8个方向的坐标位移量
int drty[8] = { -1,-1,0,1,1,1,0,-1 };//数组元素中0号为“上”然后沿顺时针依次增加

/*对棋盘空位进行打分，选择AI落子的最佳空位*/
void AI(const int status[15][15], /*nt olds[15][15],*/ int* set)
{
	int i, j, l;
	int s[2];

	//int V[17][17] = {3};
//for (i = 1; i <= 15; i++) {
//	for (j = 1; j <= 15; j++) { 
//		V[i][j] = status[i-1][j-1];
//	}
//}
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			V[i][j] = status[i][j];
		}
	}
	record* header = NULL;
	record* p = (record*)malloc(sizeof(record));
	p->next = NULL;
	header = p;
	l = simulate(V, length, /*int* set,*/p,s);
	set[0] = s[0];
	set[1] = s[1];
	//score(V, set);
}






/*判断当前局势的分数*/
void evaluate(const int V[15][15], record* m,int n/*,int *s*/)
{
	int i, j, k, t, count, score/*,*//* score1[15][15],score2[15][15]*//*,max*/;
	int tx, ty;

	//int score1[15][15][(length / 2)];
	//int score2[15][15][(length / 2)];
	//int bx, by, wx, wy;
	int cheese[15][15][8][2];
	//max = 0;
	//eval* header=NULL;
	//eval* p = (eval*)malloc(sizeof(eval));
	//p->next = NULL;
	//header = p;

	//for (n = 1; n < length; n++) {
	if (n % 2 != 0) {
		for (i = 0; i <= 14; i++) {         //行
			for (j = 0; j <= 14; j++) {     //列
				if (V[i][j] == 0)//判断该位置是否有棋子
				{
					for (k = 0; k < 8; k++)
					{
						count = 0;
						tx = i; ty = j;
						for (t = 0; t < 5; t++)//最多判断五个连子
						{
							tx += drtx[k];
							ty += drty[k];
							if (tx > 15 || tx < 1 || ty > 15 || ty < 1)//限制在棋盘内
								break;
							if (V[tx][ty] == 2)//计算某一方向黑棋个数
								count++;
							else
								break;   //判断是否为连续同一颜色棋子，不同则退出统计
						}
						cheese[i][j][k][0] = count;
					}
				}else m->mark[i][j] = INT_MIN;
			}
		}
		for (i = 0; i <= 14; i++) {         //行
			for (j = 0; j <= 14; j++)     //列
			{
				if (V[i][j] == 0)
				{
					score = 0;
					for (k = 0; k < 4; k++)
					{
						if (cheese[i][j][k][0] + cheese[i][j][k + 4][0] >= 4)
							score += 10000;
						else if (cheese[i][j][k][0] + cheese[i][j][k + 4][0] == 3)
							score += 1000;
						else if (cheese[i][j][k][0] + cheese[i][j][k + 4][0] == 2)
							score += 100;
						else if (cheese[i][j][k][0] + cheese[i][j][k + 4][0] == 1)
							score += 10;
					}
					m->mark[i][j] = score;
					//if (max < score) {
					//	tx = i;
					//	ty = j;
					//	max = score;
					//}
/*						p->Rscore[i][j] = score; */          //当前空位对白棋的分数



				}


			}
		}
		//return max;
		//s[0] = tx;
		//s[1] = ty;
		//return score;

		for (i = 0; i <= 14; i++) {         //行
			for (j = 0; j <= 14; j++) {     //列
				if (V[i][j] == 0)//判断该位置是否有棋子
				{
					for (k = 0; k < 8; k++)
					{
						count = 0;
						tx = i; ty = j;
						for (t = 0; t < 5; t++)
						{
							tx += drtx[k];
							ty += drty[k];
							if (tx > 15 || tx < 1 || ty > 15 || ty < 1)
								break;
							if (V[tx][ty] == 1)//判断黑棋个数
								count++;
							else
								break;
						}
						cheese[i][j][k][1] = count;
					}
				}
			}
		}

		for (i = 0; i <= 14; i++) {         //行
			for (j = 0; j <= 14; j++)     //列
			{
				if (V[i][j] == 0)
				{
					score = 0;
					for (k = 0; k < 4; k++)
					{
						if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] >= 4)
							score += 10000;
						else if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] == 3)
							score += 1000;
						else if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] == 2)
							score += 100;
						else if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] == 1)
							score += 10;
					}
					/*						p->Rscore[i][j] = score;      */    //当前位置对白棋的分数
					m->mark[i][j] = m->mark[i][j]- score;
				}
			}
		}

	}
	else {
		for (i = 0; i <= 14; i++) {         //行
			for (j = 0; j <= 14; j++) {     //列
				if (V[i][j] == 0)//判断该位置是否有棋子
				{
					for (k = 0; k < 8; k++)
					{
						count = 0;
						tx = i; ty = j;
						for (t = 0; t < 5; t++)
						{
							tx += drtx[k];
							ty += drty[k];
							if (tx > 15 || tx < 1 || ty > 15 || ty < 1)
								break;
							if (V[tx][ty] == 2)//判断白棋个数
								count++;
							else
								break;
						}
						cheese[i][j][k][1] = count;
					}
				}
			}
		}

		for (i = 0; i <= 14; i++) {         //行
			for (j = 0; j <= 14; j++)     //列
			{
				if (V[i][j] == 0)
				{
					score = 0;
					for (k = 0; k < 4; k++)
					{
						if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] >= 4)
							score += 10000;
						else if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] == 3)
							score += 1000;
						else if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] == 2)
							score += 100;
						else if (cheese[i][j][k][1] + cheese[i][j][k + 4][1] == 1)
							score += 10;
					}
					/*						p->Rscore[i][j] = score;      */    //当前位置对白棋的分数
					m->mark[i][j] = score;
				}
			}
		}
		//s[0] = tx;
		//s[1] = ty;
		//return score;
	}
	//p->next = (eval*)malloc(sizeof(eval));
	//p = p->next;
	//p->next = NULL;
//}
}


int simulate(int V[15][15], int len, /*int* set,*/record* p,int *s)
{
	int r[15][15];
	int max, min;
	int count, tx, ty, t,k;
	//int mark[15][15];
	int i, j;
	if (len != 0) {
		if (len == 6 || 4 || 2) {
			for (i = 0; i < 15; i++) {
				for (j = 0; j < 15; j++) {
							if (V[i][j] == 0)//判断该位置是否有棋子
							{
								for (k = 0; k < 8; k++)
								{

									count = 0;
									tx = i; ty = j;
									for (t = 0; t < 1; t++)//最多判断五个连子
									{
										tx += drtx[k];
										ty += drty[k];
										if (tx > 15 || tx < 1 || ty > 15 || ty < 1)//限制在棋盘内
											break;
										if (V[tx][ty] != 0)//计算某一方向黑棋个数
											count++;
										break;
									}


								}

								if (count != 0) {



									V[i][j] = 2;
									///*				max=max+*/simulate(V, len - 1/*, set*/, p);
									/*						p->mark[i][j]*/r[i][j] = /*max*/simulate(V, len - 1/*, set*/, p, s);
									//p->next = (record*)malloc(sizeof(record));
									//p = p->next;
									//p->next = NULL;
									V[i][j] = 0;


								}


							}




					//if (V[i][j] == 0) {
					//	




					//}
					//set[0] = i;
					//set[1] = j;
				}
			}
			max = INT_MIN;
			for (i = 0; i < 15; i++) {
				for (j = 0; j < 15; j++) {
					if (p->mark[i][j] >= max) {
						max = p->mark[i][j];
						//set[0] = i;
						//set[1] = j;
						s[0] = i;
						s[1]= j;
					}
				}
			}
			//V[i][j] = 2;
			//evaluate(V, p);
			//V[i][j] = 0;
			return max;

		}
		else {
			for (i = 0; i < 15; i++) {
				for (j = 0; j < 15; j++) {
					if (V[i][j] == 0) {



						for (k = 0; k < 8; k++)
						{
							count = 0;
							tx = i; ty = j;
							for (t = 0; t < 1; t++)//最多判断五个连子
							{
								tx += drtx[k];
								ty += drty[k];
								if (tx > 15 || tx < 1 || ty > 15 || ty < 1)//限制在棋盘内
									break;
								if (V[tx][ty] != 0)//计算某一方向黑棋个数
									count++;
								break;
							}


						}


						if (count != 0) {

							//p->next = (record*)malloc(sizeof(record));
							//p = p->next;
							//p->next = NULL;
							V[i][j] = 1;
							/*max=max+*/r[i][j] = simulate(V, len - 1/*, set*/, p, s);
							///*	p->mark[i][j] =*/ /*max*/simulate(V, len - 1/*, set*/, p);
							//p->next = (record*)malloc(sizeof(record));
							//p = p->next;
							//p->next = NULL;
							V[i][j] = 0;


						}


					}
					//set[0] = i;
					//set[1] = j;
				}
			}
			min = INT_MAX;
			for (i = 0; i < 15; i++) {
				for (j = 0; j < 15; j++) {
					if (r[i][j] <= min) {
						max = r[i][j];
						//set[0] = i;
						//set[1] = j;
						//p->x = i;
						//p->y = j;
					}
				}
			}
			//V[i][j] = 1;
			//evaluate(V, p);
			//V[i][j] = 0;
			return max;
		}
	}
	else {
		max = INT_MIN;
		evaluate(V, p,len);
		for (i = 0; i < 15; i++) {
			for (j = 0; j < 15; j++) {
				if (p->mark[i][j] > max) {
					max = p->mark[i][j];
					//set[0] = i;
					//set[1] = j;
					//p->x = i;
					//p->y = j;
				}
			}
		}
		return max;
	}
}


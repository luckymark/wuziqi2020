#include "func.hpp"
#include <iostream>
using namespace std;

box BOX[15][15];
int main()
{
	setColor(7, 7, 1);
	seat a[15 * 15];
	gen(a, 1);
	for (int i = 0; i < 15; i++) {
		printf("%d\n", a[i].score);
	}
	return 0;
}
//#pragma comment(lib,"User32.lib")
#ifndef CHECK_WIN_H
#define CHECK_WIN_H
//#pragma comment(lib,"ws2_32.lib")
bool judge(int x, int y,int Player,int chess_b[25][25]) {
	const int x_o = 20, y_o = 20;
	const int WIDTH = 30;           //¸ñ×Ó¼ä¾à
	const int SIZES = 15;
	int cnt = 0;
	for (int j = y; j < 15; j++) {
		if (chess_b[x][j] != Player)	break;
		cnt++;
	}
	for (int j = y - 1; j >= 0; j--) {
		if (chess_b[x][j] != Player)	break;
		cnt++;
	}
	if (cnt >= 5)	return true;
	cnt = 0;
	for (int i = x; i < 15; i++) {
		if (chess_b[i][y] != Player)	break;
		cnt++;
	}
	for (int i = x-1; i >= 0; i--) {
		if (chess_b[i][y] != Player)	break;
		cnt++;
	}
	if (cnt >= 5)	return true;
	cnt = 0;
	for (int i = 0; (i + x) < 15 && (i + y) < 15; i++) {
		if (chess_b[i+x][i+y] != Player)	break;
		cnt++;
	}
	for (int i = -1; (i + x) >= 0 && (i + y) >= 0; i--) {
		if (chess_b[i + x][i + y] != Player)	break;
		cnt++;
	}
	if (cnt >= 5)	return true;
	cnt = 0;
	for (int i = 0; (x-i) >= 0 && (i + y) < 15; i++) {
		if (chess_b[x - i][i + y] != Player)	break;
		cnt++;
	}
	for (int i = 1; (i + x) < 15 && (y - i) >= 0; i++) {
		if (chess_b[i + x][y - i] != Player)	break;
		cnt++;
	}
	if (cnt >= 5)	return true;
	else {
		return false;
	}
}


#endif
#pragma once

struct Chess {
	int x, y, type;
};

class ChessBoard
{
private:
	static const int maxn = 15, max_add = 5;
	int board[maxn+max_add][maxn+max_add];
	int pos_score[maxn + 5][maxn + 5], type[21][6], value[21];		// 21 ÖÖÆåÐÍ

public:
	enum {
		blank, black, white
	};
	const static int X0 = 22, Y0 = 22, DEL = 35, CHESS_R = 10, UPLIM = maxn;

	ChessBoard();
	~ChessBoard();

	HWND drawBoard();
	bool writeBoard(Chess c);	// »­Æå×Ó
	int changeColor(int now);
	int getType(int x, int y);
	void changeType(int x, int y, int type);
	int evaluate(int color);
	int analyseNode(int x, int y);
};



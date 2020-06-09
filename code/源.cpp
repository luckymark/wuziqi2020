#include "Checkerboard.h"
#include "Player.h"
#include "ChessAI.h"
#include <conio.h>

int main() {
	Checkerboard board;
	board.print_init();
	board.print_board();
	Player me(BLACKCHESS);
	ChessAI other(WHITECHESS);
	bool flag = true;
	while (1) {
		if (flag)
		{
			if (me.player_set_chess(board))
			{
				break;
			}
		}
		else {
			if (other.AI_set_chess(board))
			{
				break;
			}
		}
		flag = !flag;
	}
	closegraph();
	return 0;
}
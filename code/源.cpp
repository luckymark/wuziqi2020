#include "Checkerboard.h"
#include "Player.h"
#include <conio.h>

int main() {
	Checkerboard board;
	board.print_init();
	board.print_board();
	Player me(BLACKCHESS), other(WHITECHESS);
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
			if (other.player_set_chess(board))
			{
				break;
			}
		}
		flag = !flag;
	}
	closegraph();
	return 0;
}
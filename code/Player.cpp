#include "Player.h"
#include <conio.h>

bool Player::player_set_chess(Checkerboard& board)
{
	int x, y;
	while (true) {
		catch_mouth(x, y);
		if (set_chess(board, x, y))
		{
			break;
		}
	}
	board.print_chess();
	if (board.judge(x, y, color))
	{
		board.print_win();
		_getch();
		return true;
	}
	return false;
}

bool Player::set_chess(Checkerboard& board, int x, int y)
{
	return board.set_chess(x, y, color);
}

int* Player::get_line(Checkerboard& board, int x, int y, int front)
{
	int* line;
	line = board.get_line(x, y, front);
	return line;
}

void Player::catch_mouth(int& x, int& y) {
	while (true) {
		MOUSEMSG mouse = GetMouseMsg();
		if (mouse.uMsg == WM_LBUTTONUP) {
			x = (mouse.y + 20) / 40 - 1;
			y = (mouse.x + 20) / 40 - 1;
			FlushMouseMsgBuffer();
			return;
		}
	}
}

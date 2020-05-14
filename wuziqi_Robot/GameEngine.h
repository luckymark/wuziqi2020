#pragma once
enum PlayerColor
{
    PLAYER_BLACK = 0,
    PLAYER_WHITE
};
enum ChessColor
{
    CHESS_EMPTY = 0,
    CHESS_BLACK,
    CHESS_WHITE
};
typedef struct {
    int map[15][15];
} Score;
typedef struct {
    int map[15][15];
    int aiPlayerColor;
    int blackBanned;
    Score score;
}GameEngine;


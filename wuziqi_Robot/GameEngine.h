#pragma once

enum PlayerColor
{
    PLAYER_BLACK = 0,
    PLAYER_WHITE = 1
};
enum ChessColor
{
    CHESS_EMPTY = 0,
    CHESS_BLACK = 1,
    CHESS_WHITE = 2
};
typedef struct {
    int map[15][15];
} SquareMap;
typedef SquareMap TupleScore;
typedef struct {
    int list[225];
}ListMap;
typedef ListMap TuplePriorScore;
typedef struct GameEngine {
    SquareMap squareMap;
    int playerColor;
    int blackBanned;
}GameEngine;




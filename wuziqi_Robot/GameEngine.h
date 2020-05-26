#pragma once
#include <string.h>
#include <stdlib.h>
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
} SquareMap;
typedef SquareMap TupleScore;
typedef struct {
    int list[225];
}ListMap;
typedef ListMap TuplePriorScore;
typedef struct {
    SquareMap squareMap;
    int playerColor;
    int blackBanned;
}GameEngine;




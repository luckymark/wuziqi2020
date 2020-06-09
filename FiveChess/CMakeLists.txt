cmake_minimum_required(VERSION 3.15)
project(FiveChess C)

set(CMAKE_C_STANDARD 99)

add_executable(FiveChess main.c AI.h Board.h)
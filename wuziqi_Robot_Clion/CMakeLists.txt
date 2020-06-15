cmake_minimum_required(VERSION 3.15)
project(wuziqi_Robot_Clion C)

set(CMAKE_C_STANDARD 99)

add_library(wuziqi_Robot_Clion SHARED library.c library.h)
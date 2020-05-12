cmake_minimum_required(VERSION 3.15)

project(wuziqi2020)

set(CMAKE_CXX_STANDARD 11)

link_libraries(
        D:/CodeBlocks/MinGW/lib/libgraphics.a
        D:/CodeBlocks/MinGW/lib/libgdi32.a
        D:/CodeBlocks/MinGW/lib/libimm32.a
        D:/CodeBlocks/MinGW/lib/libmsimg32.a
        D:/CodeBlocks/MinGW/lib/libole32.a
        D:/CodeBlocks/MinGW/lib/liboleaut32.a
        D:/CodeBlocks/MinGW/lib/libwinmm.a
        D:/CodeBlocks/MinGW/lib/libuuid.a
        )
add_executable(Cmd WIN32 wuziqi.cpp initWindow.cpp initWindow.h game.cpp game.h game_algorithm.cpp)




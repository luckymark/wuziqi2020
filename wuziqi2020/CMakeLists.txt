# CMakeList.txt: 五子棋AI 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("五子棋AI")

# 将源代码添加到此项目的可执行文件。
add_executable (CMakeTarget "interface.cpp" "draw.cpp" "math.cpp" "getPosition.cpp" "func.hpp")
#add_executable (CMakeTarget "test.cpp" "func.hpp")

# TODO: 如有需要，请添加测试并安装目标。

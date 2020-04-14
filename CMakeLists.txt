#cmake_minimum_required(VERSION 3.15)
#project(chessFinal)
#
#set(CMAKE_CXX_STANDARD 11)
#
#add_executable(chessFinal main.cpp)
cmake_minimum_required(VERSION 3.8)
project(chessFinal)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH D:/qt/5.9/mingw53_32) #这里需要填入自己安装的路径


find_package(Qt5Widgets)
find_package( Qt5Core)
find_package( Qt5Gui)

set(UI_FILES)

set(RC_FILES)

set(QRC_FILES)

set(SOURCE_FILES main.cpp )

add_executable(chessFinal WIN32 ${RC_FILES}${SOURCE_FILES}${UI_FILES}${QRC_FILES} board.cpp board.h chessglobalconst.h chessAI.cpp init_chess_type.cpp)

target_link_libraries(chessFinal Qt5::Widgets)

qt5_use_modules(chessFinal Core Widgets Gui)

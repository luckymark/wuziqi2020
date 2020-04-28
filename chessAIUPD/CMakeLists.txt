cmake_minimum_required(VERSION 3.15)
project(chessAIUPD)

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
add_executable(chessAIUPD main.cpp board.cpp board.h chessglobalconst.h alphabeta.cpp alphabeta.h chessglobalvariable.cpp chessglobalvariable.h chessstruct.h chesslib.h chess_init_type.cpp chess_init_type.h analysis_kill.cpp analysis_kill.h chess_button.cpp chess_button.h)

target_link_libraries(chessAIUPD Qt5::Widgets)
string(REPLACE "-O2" "-Os" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
qt5_use_modules(chessAIUPD Core Widgets Gui)
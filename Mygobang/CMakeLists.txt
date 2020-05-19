cmake_minimum_required(VERSION 3.15)
project(Mygobang)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH D:/Qt/Qt5.14.1/5.14.1/mingw73_32) #这里需要填入自己安装的路径


find_package(Qt5Widgets)
find_package( Qt5Core)
find_package( Qt5Gui)

set(UI_FILES)

set(RC_FILES)

set(QRC_FILES)

set(SOURCE_FILES main.cpp mainwindow.cpp mainwindow.h  AI.cpp AI.h)

add_executable(Mygobang WIN32 ${RC_FILES}${SOURCE_FILES}${UI_FILES}${QRC_FILES} chessboard.cpp chessboard.h)

target_link_libraries(Mygobang Qt5::Widgets)

qt5_use_modules(Mygobang Core Widgets Gui)
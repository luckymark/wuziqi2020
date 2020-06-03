cmake_minimum_required(VERSION 3.15)
project(wuziqi2020)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(wuziqi2020 main.cpp Window.cpp Window.h Game.cpp Game.h points.h)

target_link_libraries(wuziqi2020 Qt5::Widgets)

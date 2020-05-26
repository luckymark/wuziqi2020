QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoBang
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    GameModel.cpp

HEADERS  += mainwindow.h \
    GameModel.h

RESOURCES += \
    resource.qrc

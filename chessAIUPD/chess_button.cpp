//
// Created by hw730 on 2020/4/23.
//

#include "chess_button.h"
void setbutton(QPushButton &_button,QPushButton &_button1)
{

    _button.setText(QString("右键重新开始"));
    _button.resize(100,100);
    _button1.setText(QString("右键悔棋"));
    _button1.resize(100,100);
    _button1.move(0,100);
}
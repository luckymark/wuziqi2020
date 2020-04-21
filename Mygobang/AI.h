//
// Created by 彭琳峰 on 2020/4/21.
//

#pragma once
#include<QPoint>
class AI {
public:
    QPoint& AI_Turn(int x, int y);
    void culculateScore(int chessboard[][]);
private:
    QPoint now;

};
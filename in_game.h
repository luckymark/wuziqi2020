#ifndef IN_GAME_H
#define IN_GAME_H
#include <mainwindow.h>
#include <mouseveents.h>
#include <check_win.h>
#include <minmax.h>
#include <score_count.h>

void MainWindow::in_game(){
    if(player==1){
        MainWindow::mouseReleaseEvent(QMouseEvent *e);

    }
}

#endif // IN_GAME_H

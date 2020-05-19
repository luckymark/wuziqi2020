#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include<qlabel.h>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.move ((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);
    return a.exec();
}
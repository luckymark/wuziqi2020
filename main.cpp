#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::addLibraryPath("./plugins");
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

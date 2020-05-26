#include "QtGuiApplication2.h"
#include <QtWidgets/QApplication>
#include<qlabel.h>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiApplication2 w;
	w.show();
	return a.exec();
}

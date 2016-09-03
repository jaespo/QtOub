#include "qtoub.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtOub w;
	w.show();
	return a.exec();
}

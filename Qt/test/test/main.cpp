#include "test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	test w;
	w.show();
	return a.exec();
}

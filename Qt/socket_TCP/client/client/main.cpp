#include "client.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	client w;
	w.show();
	return a.exec();
}

#include "timer_example.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Timer_Example w;
	w.show();
	return a.exec();
}

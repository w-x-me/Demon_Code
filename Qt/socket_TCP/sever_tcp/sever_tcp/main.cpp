#include "sever_tcp.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	sever_tcp w;
	w.show();
	return a.exec();
}

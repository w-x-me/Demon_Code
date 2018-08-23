#include "mmi_server_demon.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MMI_Server_Demon w;
	w.show();
	return a.exec();
}

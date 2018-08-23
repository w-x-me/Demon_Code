#include "qt_halcon_image_deal.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Qt_Halcon_Image_Deal w;
	w.show();
	return a.exec();
}

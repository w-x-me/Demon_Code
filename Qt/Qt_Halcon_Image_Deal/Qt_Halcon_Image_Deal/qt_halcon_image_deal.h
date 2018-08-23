#ifndef QT_HALCON_IMAGE_DEAL_H
#define QT_HALCON_IMAGE_DEAL_H

#include <QtWidgets/QMainWindow>
#include "ui_qt_halcon_image_deal.h"
#pragma execution_character_set("utf-8")
#include "HalconCpp.h"
class Qt_Halcon_Image_Deal : public QMainWindow
{
	Q_OBJECT

public:
	Qt_Halcon_Image_Deal(QWidget *parent = 0);
	~Qt_Halcon_Image_Deal();

	HalconCpp::HTuple hv_Width, hv_Height, hv_WindowID;
	HalconCpp::HObject ho_Image, ho_Region, ho_ConnectedRegions, ho_SelectedRegions;
	Hlong winID;
private slots:
	void My_read_image();
	void My_deal_image();

private:
	Ui::Qt_Halcon_Image_DealClass ui;
};

#endif // QT_HALCON_IMAGE_DEAL_H

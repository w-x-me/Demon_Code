#ifndef TEMPLATE_MACTH_H
#define TEMPLATE_MACTH_H

#include <QtWidgets/QMainWindow>
#include "ui_template_macth.h"
#include "HalconCpp.h"
#include "Find_ncc_model_exposure.h"
class Template_Macth : public QMainWindow
{
	Q_OBJECT

public:
	find_ncc_model_exposure FNCME;
	Template_Macth(QWidget *parent = 0);
	int Timer;
	int index;
	~Template_Macth();
public:
	void timerEvent(QTimerEvent*);
	void Start();
signals:
	void ho_Image_show_signal(int a);
	void init_windows_signal(QString str);
	void circle_Image_show_signal(int b, QString bstr);
private slots:
	void Template_Macth_Method();
	void Template_Macth1_Method();
	void ho_Image_show(int a);
	void init_windows(QString str);
	void circle_Image_show(int b , QString bstr);
	void Template_Macth2_Method();
private:
	Ui::Template_MacthClass ui;

};

#endif // TEMPLATE_MACTH_H

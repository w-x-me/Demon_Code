#include "timer_example.h"

Timer_Example::Timer_Example(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	index = 0;
}

void Timer_Example::Image_Show()
{
	if (index == 0)
	{
		ui.Image_Show_label->setPixmap(QPixmap("1.bmp").scaled(ui.Image_Show_label->width(), ui.Image_Show_label->height()));
	}
	if (index == 1)
	{
		ui.Image_Show_label->setPixmap(QPixmap("2.bmp").scaled(ui.Image_Show_label->width(), ui.Image_Show_label->height()));
	}
	if (index == 2)
	{
		ui.Image_Show_label->setPixmap(QPixmap("3.bmp").scaled(ui.Image_Show_label->width(), ui.Image_Show_label->height()));
	}
	if (index == 3)
	{
		ui.Image_Show_label->setPixmap(QPixmap("4.bmp").scaled(ui.Image_Show_label->width(), ui.Image_Show_label->height()));
	}
	if (index == 4)
	{
		ui.Image_Show_label->setPixmap(QPixmap("5.bmp").scaled(ui.Image_Show_label->width(), ui.Image_Show_label->height()));
	}
	if (index == 5)
	{
		ui.Image_Show_label->setPixmap(QPixmap("6.bmp").scaled(ui.Image_Show_label->width(), ui.Image_Show_label->height()));
	}
	if (index == 6)
	{
		ui.Image_Show_label->setPixmap(QPixmap("7.bmp").scaled(ui.Image_Show_label->width(), ui.Image_Show_label->height()));
	}
	index += 1;
	if (index == 7)
	{
		if (Timer != -1)
		{
			killTimer(Timer);
			Timer = -1;
		}
		index = 0;
		ui.Start_btn->setEnabled(true);
	}
}

void Timer_Example::timerEvent(QTimerEvent*)
{
	Image_Show();
}

void Timer_Example::Start()
{
	Timer = startTimer(2000);
	ui.Start_btn->setEnabled(false);
}

Timer_Example::~Timer_Example()
{

}

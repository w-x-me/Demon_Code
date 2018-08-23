#ifndef TIMER_EXAMPLE_H
#define TIMER_EXAMPLE_H

#include <QtWidgets/QMainWindow>
#include "ui_timer_example.h"

class Timer_Example : public QMainWindow
{
	Q_OBJECT

public:
	Timer_Example(QWidget *parent = 0);
	~Timer_Example();
	long Timer;
	int index;
public:
	void timerEvent(QTimerEvent*);
	void Image_Show();

private slots:
	void Start();
private:
	Ui::Timer_ExampleClass ui;
};

#endif // TIMER_EXAMPLE_H

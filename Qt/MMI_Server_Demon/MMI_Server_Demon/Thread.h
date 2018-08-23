#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <iostream>
#include<QLabel.h>
#include<qpushbutton.h>
#include<qlineedit.h>
#include<QtNetwork/QtNetwork>
#pragma execution_character_set("utf-8")
class Thread : public QThread
{
	Q_OBJECT
public:
	QLabel *thread_label;
	QPushButton *thread_btn;
	QLineEdit *thread_let;
	QTcpSocket **thread_socket;
	int socket_node;
	bool run_state;
	Thread();
	void setParam(QLabel *label, QPushButton *btn, QLineEdit *let, QTcpSocket **socket,int node);
protected:
	void run();
private:
	int i;
};
#endif // THREAD_H
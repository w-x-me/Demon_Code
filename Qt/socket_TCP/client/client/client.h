#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets/QMainWindow>
#include "ui_client.h"
#include<QtNetwork/QtNetwork>
class client : public QMainWindow
{
	Q_OBJECT

public:
	client(QWidget *parent = 0);
	~client();
	QTcpSocket* m_socket=NULL;
private slots:
	void connect_server();
	void send_server();
	void readyread();
private:
	Ui::clientClass ui;
};

#endif // CLIENT_H

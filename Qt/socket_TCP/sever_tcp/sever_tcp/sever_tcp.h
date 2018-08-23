#ifndef SEVER_TCP_H
#define SEVER_TCP_H

#include <QtWidgets/QMainWindow>
#include "ui_sever_tcp.h"
#include<QtNetwork/QtNetwork>


class sever_tcp : public QMainWindow
{
	Q_OBJECT

public:
	sever_tcp(QWidget *parent = 0);
	~sever_tcp();
	QTcpSocket* m_socket = NULL;//定义通讯套接字
	QTcpServer* m_server = NULL;
	
	void Server_New_Connect();
	void socket_Read_Data();//收到客户端发送消息处理
	void socket_Disconnect();//客户端断开连接处理
private slots:
	void My_Server_Start();
	void My_Send_Info();
private:
	Ui::sever_tcpClass ui;
};

#endif // SEVER_TCP_H

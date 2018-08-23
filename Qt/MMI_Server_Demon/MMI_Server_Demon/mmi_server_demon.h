#ifndef MMI_SERVER_DEMON_H
#define MMI_SERVER_DEMON_H

#include <QtWidgets/QMainWindow>
#include "ui_mmi_server_demon.h"
#include<QtNetwork/QtNetwork>
#include<iostream>
#include<QList>
#include"Thread.h"
#include<afxwin.h>
#pragma execution_character_set("utf-8")
class MMI_Server_Demon : public QMainWindow
{
	Q_OBJECT
	
public:
	QTcpServer* m_server=NULL;
	QTcpSocket* m_socket[10];
	int socket_state[10];
	Thread thread[10];
	CWinThread* thread_windows;
	int i = 0;
	MMI_Server_Demon(QWidget *parent = 0);
	~MMI_Server_Demon();
	void Server_New_Connect();
	//DWORD WINAPI ThreadProc5();
private slots:
void My_Server_Start();

void socket1_Disconnect();
void Dev_Send1();

void socket2_Disconnect();
void Dev_Send2();

void socket3_Disconnect();
void Dev_Send3();

void socket4_Disconnect();
void Dev_Send4();

void socket5_Disconnect();
void Dev_Send5();

void socket6_Disconnect();
void Dev_Send6();

void socket7_Disconnect();
void Dev_Send7();

void socket8_Disconnect();
void Dev_Send8();

void socket9_Disconnect();
void Dev_Send9();

void socket10_Disconnect();
void Dev_Send10();

private:
	Ui::MMI_Server_DemonClass ui;
};

#endif // MMI_SERVER_DEMON_H

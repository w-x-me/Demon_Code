#ifndef THREAD_H
#define THREAD_H
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include <WS2tcpip.h>
#include <WinSock2.H>
#include <iostream>
#include <QString>
#include <QThread>
#include <sstream>
#pragma comment(lib, "ws2_32.lib") 
class ListenThread: public QThread
{
	Q_OBJECT
public:
	ListenThread();
	~ListenThread();
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);
	fd_set allSockSet;
	int result;
	QString ip;
	QString port;
	void Send_Content(QString content,int socket_number);
	void run();
signals:
	//参数作用：服务器收到的内容，并且显示到界面
	void content_signal(QString str);
	//参数1：对socket的描述符。参数2：处理socket的方法
	void socket_signal(int numb, int type);
};
#endif // THREAD_H
#ifndef MAIN_UI_H
#define MAIN_UI_H
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_main-ui.h"
#include "listen-thread.h"
#include<QString>
#include<QDateTime>
class MainUi : public QMainWindow
{
	Q_OBJECT

public:
	MainUi(QWidget *parent = 0);
	~MainUi();
	int client_socket[5];
	ListenThread my_listen_thread;
	void Connet_State_Show(int numb, int type);
public slots:
	void Send_Content1();
	void Send_Content2();
	void Send_Content3();
	void Send_Content4();
	void Send_Content5();
	void Content_Show(QString content);//服务器收到的信息显示
	void Start_Listen_Thread();//开启服务器监听线程
	void Socket_Connect_State(int numb,int type);
private:
	void Init_Socket_State();
	Ui::MainUiClass ui;
};

#endif // MAIN_UI_H

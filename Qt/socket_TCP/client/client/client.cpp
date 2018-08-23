#include "client.h"
#include<iostream>
#include<stdio.h>
#include<qdebug.h>
#pragma execution_character_set("utf-8")
client::client(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_socket = new QTcpSocket;
	//connect(this->m_socket, SIGNAL(readyRead()), this, SLOT(readyread()));
	connect(m_socket, &QTcpSocket::readyRead, this, &client::readyread);
	qDebug() << "你好";
	
}
void client::readyread()
{
	QString buffer;
	buffer = m_socket->readAll();
	qDebug() << buffer;
	qDebug() << "read_server";
	
}
void client::connect_server()
{
	m_socket->connectToHost("192.168.1.53", 8002);
	qDebug() << "connect_server";
}
void client::send_server()
{
	m_socket->write("你好服务器\n");
	qDebug() << "send_server";
}
client::~client()
{

}

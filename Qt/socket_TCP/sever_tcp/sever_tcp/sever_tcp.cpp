#include "sever_tcp.h"
#pragma execution_character_set("utf-8")
sever_tcp::sever_tcp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_server = new QTcpServer();
	m_socket = new QTcpSocket();
	connect(this->m_server, &QTcpServer::newConnection, this, &sever_tcp::Server_New_Connect);
	
}
void sever_tcp::My_Server_Start()
{
	
	if (ui.Server_Start_Bt->text() == "开启")
	{
		qDebug() << "启动服务器";
		QHostAddress IP("192.168.1.53");
		quint16 server_port = 8002;
		if (m_server->listen(IP, server_port))
		{
			qDebug() << "开启监听";
			ui.Server_Start_Bt->setText("关闭");
		}
		else
		{
			qDebug() << "监听失败";
			ui.Server_Start_Bt->setText("开启");
		}
		return;
	}
	if (ui.Server_Start_Bt->text() == "关闭")
	{
		qDebug() << "关闭连接";
		ui.Server_Start_Bt->setText("开启");
	}
	return;
}
void sever_tcp::Server_New_Connect()
{
	qDebug() << "收到新连接";
	m_socket = m_server->nextPendingConnection();//获取客户端连接
	QObject::connect(m_socket, &QTcpSocket::readyRead, this, &sever_tcp::socket_Read_Data);
	//QObject::connect(m_socket, &QTcpSocket::disconnected, this, &sever_tcp::socket_Disconnect);
}
void sever_tcp::socket_Read_Data()
{
	qDebug() << "收送消息";
	QString buffer;
	buffer = m_socket->readAll();
	ui.plainTextEdit->setPlainText(buffer);
}

void sever_tcp::socket_Disconnect()
{
	qDebug() << "客户端断开连接";
}

void sever_tcp::My_Send_Info()
{
	qDebug() << "发送消息";
	QString buffer = ui.textEdit->toPlainText();
	qint64 writeResult = m_socket->write(buffer.toLatin1()+'\n');
	bool BoolFlush = m_socket->flush();
	if (writeResult != -1 && BoolFlush == 1)
	{
		qDebug() << "发送消息成功";
	}

}
sever_tcp::~sever_tcp()
{
	m_server->close();
	m_server->deleteLater();
}

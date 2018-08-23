#include "mmi_server_demon.h"

MMI_Server_Demon::MMI_Server_Demon(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	for (int i = 0; i < 10; i++)
	{
		socket_state[i] = 0;
	}
	
}

void MMI_Server_Demon::My_Server_Start()
{
	if (ui.Server_Start_Bt->text() == "开启")
	{
		m_server = new QTcpServer;
		connect(this->m_server, &QTcpServer::newConnection, this, &MMI_Server_Demon::Server_New_Connect);
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
		m_server->close();
		m_server->deleteLater();
		delete m_server;
		m_server = NULL;
	}
	return;
}

void MMI_Server_Demon::Server_New_Connect()
{
	qDebug() << "收到新连接";
	for (int i = 0; i < 10; i++)
	{
		if (socket_state[i] == 0)
		{
			if (i == 0)
			{
				qDebug() << "对设备1的连接进行处理，并且开启线程，" << endl;
				m_socket[i] = m_server->nextPendingConnection();//获取客户端连接
				QObject::connect(m_socket[i], &QTcpSocket::disconnected, this, &MMI_Server_Demon::socket1_Disconnect);
				thread[i].setParam(ui.read_1, ui.Send_Bt_1, ui.send_1, &m_socket[i], i);
				thread[0].run_state = true;
				socket_state[i] = 1;
				thread[i].start();
				break;
			}
		
			if (i == 1)
			{
				qDebug() << "对设备2的连接进行处理，并且开启线程，" << endl;
				m_socket[i] = m_server->nextPendingConnection();//获取客户端连接
				thread[1].run_state = true;
				QObject::connect(m_socket[i], &QTcpSocket::disconnected, this, &MMI_Server_Demon::socket2_Disconnect);
				thread[i].setParam(ui.read_2, ui.Send_Bt_2, ui.send_2, &m_socket[i], i);
				thread[i].start();
				socket_state[i] = 1;
				break;
			}

			if (i == 2)
			{
				qDebug() << "对设备3的连接进行处理，并且开启线程，" << endl;
				m_socket[i] = m_server->nextPendingConnection();//获取客户端连接
				QObject::connect(m_socket[i], &QTcpSocket::disconnected, this, &MMI_Server_Demon::socket3_Disconnect);
				thread[i].setParam(ui.read_3, ui.Send_Bt_3, ui.send_3, &m_socket[i], i);
				thread[2].run_state = true;
				thread[i].start();
				socket_state[i] = 1;
				break;
			}

			if (i == 3)
			{
				qDebug() << "对设备4的连接进行处理，并且开启线程，" << endl;
				
				m_socket[i] = m_server->nextPendingConnection();//获取客户端连接
				QObject::connect(m_socket[i], &QTcpSocket::disconnected, this, &MMI_Server_Demon::socket4_Disconnect);
				thread[i].setParam(ui.read_4, ui.Send_Bt_4, ui.send_4, &m_socket[i], i);
				thread[3].run_state = true;
				thread[i].start();
				socket_state[i] = 1;
				break;
			}

			if (i == 4)
			{
				qDebug() << "对设备5的连接进行处理，并且开启线程，" << endl;
				m_socket[i] = m_server->nextPendingConnection();//获取客户端连接
				QObject::connect(m_socket[i], &QTcpSocket::disconnected, this, &MMI_Server_Demon::socket5_Disconnect);
				thread[i].setParam(ui.read_5, ui.Send_Bt_5, ui.send_5, &m_socket[i], i);
				thread[4].run_state = true;
				thread[i].start();
				socket_state[i] = 1;
				break;
			}

			if (i == 5)
			{
				qDebug() << "对设备6的连接进行处理，并且开启线程，" << endl;
				m_socket[i] = m_server->nextPendingConnection();//获取客户端连接
				QObject::connect(m_socket[i], &QTcpSocket::disconnected, this, &MMI_Server_Demon::socket6_Disconnect);
				thread[i].setParam(ui.read_6, ui.Send_Bt_6, ui.send_6, &m_socket[i], i);
				thread[5].run_state = true;
				thread[i].start();
				socket_state[i] = 1;
				break;
			}

			if (i == 6)
			{

				qDebug() << "对设备7的连接进行处理，并且开启线程，" << endl;
				m_socket[i] = m_server->nextPendingConnection();//获取客户端连接
				QObject::connect(m_socket[i], &QTcpSocket::disconnected, this, &MMI_Server_Demon::socket7_Disconnect);
				thread[i].setParam(ui.read_7, ui.Send_Bt_7, ui.send_7, &m_socket[i],i);
				thread[6].run_state = true;
				thread[i].start();
				socket_state[i] = 1;
				break;
			}

			if (i == 7)
			{
				qDebug() << "对设备8的连接进行处理，并且开启线程，" << endl;
				m_socket[i] = m_server->nextPendingConnection();//获取客户端连接
				QObject::connect(m_socket[i], &QTcpSocket::disconnected, this, &MMI_Server_Demon::socket8_Disconnect);
				thread[i].setParam(ui.read_8, ui.Send_Bt_8, ui.send_8, &m_socket[i], i);
				thread[7].run_state = true;
				thread[i].start();
				socket_state[i] = 1;
				break;
			}

			if (i == 8)
			{
				qDebug() << "对设备9的连接进行处理，并且开启线程，" << endl;
				m_socket[i] = m_server->nextPendingConnection();//获取客户端连接
				QObject::connect(m_socket[i], &QTcpSocket::disconnected, this, &MMI_Server_Demon::socket9_Disconnect);
				thread[i].setParam(ui.read_9, ui.Send_Bt_9, ui.send_9, &m_socket[i], i);
				thread[8].run_state = true;
				thread[i].start();
				socket_state[i] = 1;
				break;
			}

			if (i == 9)
			{
				qDebug() << "对设备1的连接进行处理，并且开启线程，" << endl;
				m_socket[i] = m_server->nextPendingConnection();//获取客户端连接
				QObject::connect(m_socket[i], &QTcpSocket::disconnected, this, &MMI_Server_Demon::socket10_Disconnect);
				thread[i].setParam(ui.read_10, ui.Send_Bt_10, ui.send_10, &m_socket[i], i);
				thread[9].run_state = true;
				thread[i].start();
				socket_state[i] = 1;
				break;
			}
				
		}
	}
	
	
}

void MMI_Server_Demon::Dev_Send1()
{
	QString send_cont = ui.send_1->text();
	qint64 writeResult = m_socket[0]->write(send_cont.toLatin1() + '\n');
	bool BoolFlush = m_socket[0]->flush();
	if (writeResult != -1 && BoolFlush == 1)
	{
		qDebug() << "设备1发送消息成功";
	}
}
void MMI_Server_Demon::socket1_Disconnect()
{
	qDebug() << "设备1连接断开";
	socket_state[0] = 0;
	thread[0].run_state = false;
	ui.read_1->setText("连接断开");
}

void MMI_Server_Demon::Dev_Send2()
{
	QString send_cont = ui.send_2->text();
	qint64 writeResult = m_socket[1]->write(send_cont.toLatin1() + '\n');
	bool BoolFlush = m_socket[1]->flush();
	if (writeResult != -1 && BoolFlush == 1)
	{
		qDebug() << "设备1发送消息成功";
	}
	
}
void MMI_Server_Demon::socket2_Disconnect()
{
	socket_state[1] = 0;
	thread[0].run_state = false;
	ui.read_2->setText("连接断开");
}

void MMI_Server_Demon::Dev_Send3()
{
	QString send_cont = ui.send_3->text();
	qint64 writeResult = m_socket[2]->write(send_cont.toLatin1() + '\n');
	bool BoolFlush = m_socket[2]->flush();
	if (writeResult != -1 && BoolFlush == 1)
	{
		qDebug() << "设备3发送消息成功";
	}

}
void MMI_Server_Demon::socket3_Disconnect()
{
	socket_state[2] = 0;
	thread[2].run_state = false;
	ui.read_3->setText("连接断开");
}

void MMI_Server_Demon::Dev_Send4()
{
	QString send_cont = ui.send_4->text();
	qint64 writeResult = m_socket[3]->write(send_cont.toLatin1() + '\n');
	bool BoolFlush = m_socket[3]->flush();
	if (writeResult != -1 && BoolFlush == 1)
	{
		qDebug() << "设备4发送消息成功";
	}

}
void MMI_Server_Demon::socket4_Disconnect()
{
	socket_state[3] = 0;
	thread[3].run_state = false;
	ui.read_4->setText("连接断开");
}


void MMI_Server_Demon::Dev_Send5()
{
	QString send_cont = ui.send_5->text();
	qint64 writeResult = m_socket[4]->write(send_cont.toLatin1() + '\n');
	bool BoolFlush = m_socket[4]->flush();
	if (writeResult != -1 && BoolFlush == 1)
	{
		qDebug() << "设备1发送消息成功";
	}
}
void MMI_Server_Demon::socket5_Disconnect()
{
	socket_state[4] = 0;
	thread[4].run_state = false;
	ui.read_5->setText("连接断开");
}


void MMI_Server_Demon::Dev_Send6()
{
	QString send_cont = ui.send_6->text();
	qint64 writeResult = m_socket[5]->write(send_cont.toLatin1() + '\n');
	bool BoolFlush = m_socket[5]->flush();
	if (writeResult != -1 && BoolFlush == 1)
	{
		qDebug() << "设备1发送消息成功";
	}

}
void MMI_Server_Demon::socket6_Disconnect()
{
	socket_state[5] = 0;
	thread[5].run_state = false;
	ui.read_6->setText("连接断开");
}


void MMI_Server_Demon::Dev_Send7()
{
	QString send_cont = ui.send_7->text();
	qint64 writeResult = m_socket[6]->write(send_cont.toLatin1() + '\n');
	bool BoolFlush = m_socket[6]->flush();
	if (writeResult != -1 && BoolFlush == 1)
	{
		qDebug() << "设备7发送消息成功";
	}

}
void MMI_Server_Demon::socket7_Disconnect()
{
	socket_state[6] = 0;
	thread[6].run_state = false;
	ui.read_7->setText("连接断开");
}


void MMI_Server_Demon::Dev_Send8()
{
	QString send_cont = ui.send_8->text();
	qint64 writeResult = m_socket[7]->write(send_cont.toLatin1() + '\n');
	bool BoolFlush = m_socket[7]->flush();
	if (writeResult != -1 && BoolFlush == 1)
	{
		qDebug() << "设备8发送消息成功";
	}

}
void MMI_Server_Demon::socket8_Disconnect()
{
	socket_state[7] = 0;
	thread[7].run_state = false;
	ui.read_8->setText("连接断开");
}


void MMI_Server_Demon::Dev_Send9()
{
	QString send_cont = ui.send_9->text();
	qint64 writeResult = m_socket[8]->write(send_cont.toLatin1() + '\n');
	bool BoolFlush = m_socket[8]->flush();
	if (writeResult != -1 && BoolFlush == 1)
	{
		qDebug() << "设备9发送消息成功";
	}

}
void MMI_Server_Demon::socket9_Disconnect()
{
	socket_state[8] = 0;
	thread[8].run_state = false;
	ui.read_9->setText("连接断开");
}

void MMI_Server_Demon::Dev_Send10()
{
	QString send_cont = ui.send_10->text();
	qint64 writeResult = m_socket[9]->write(send_cont.toLatin1() + '\n');
	bool BoolFlush = m_socket[9]->flush();
	if (writeResult != -1 && BoolFlush == 1)
	{
		qDebug() << "设备10发送消息成功";
	}

}
void MMI_Server_Demon::socket10_Disconnect()
{
	socket_state[9] = 0;
	thread[9].run_state = false;
	ui.read_10->setText("连接断开");
}

/*DWORD WINAPI MMI_Server_Demon::ThreadProc5()
{
	ui.read_1->setText("windows线程");
	return 0;
}*/

MMI_Server_Demon::~MMI_Server_Demon()
{

}

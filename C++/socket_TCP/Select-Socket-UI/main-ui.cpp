#include "main-ui.h"

MainUi::MainUi(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.textEdit->setEnabled(false);
	Init_Socket_State();
	connect(&(this->my_listen_thread), SIGNAL(content_signal(QString)), this, SLOT(Content_Show(QString)));
	connect(&(this->my_listen_thread), SIGNAL(socket_signal(int, int)), this, SLOT(Socket_Connect_State(int,int)));
}

void MainUi::Content_Show(QString content)
{
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy/MM/dd hh:mm:ss.zzz ddd");
	ui.textEdit->append(current_date);
	ui.textEdit->append(content);
}

void  MainUi::Start_Listen_Thread()
{
	my_listen_thread.ip=ui.ip_le->text();
	my_listen_thread.port = ui.port_le->text();
	my_listen_thread.start();

}

void MainUi::Connet_State_Show(int numb, int type)
{
	if (numb == 0)
	{
		if (type == 1)
		{
			ui.status_1->setText("连接");
			ui.send_btn1->setEnabled(true);
		}
		if (type == -1)
		{
			ui.status_1->setText("未连接");
			ui.send_btn1->setEnabled(false);
		}
	}
	if (numb == 1)
	{
		if (type == 1)
		{
			ui.status_2->setText("连接");
			ui.send_btn2->setEnabled(true);
		}
		if (type == -1)
		{
			ui.status_2->setText("未连接");
			ui.send_btn2->setEnabled(false);
		}
	}

	if (numb == 2)
	{
		if (type == 1)
		{
			ui.status_3->setText("连接");
			ui.send_btn3->setEnabled(true);
		}
		if (type == -1)
		{
			ui.status_3->setText("未连接");
			ui.send_btn3->setEnabled(false);
		}
	}

	if (numb == 3)
	{
		if (type == 1)
		{
			ui.status_4->setText("连接");
			ui.send_btn4->setEnabled(true);
		}
		if (type == -1)
		{
			ui.status_4->setText("未连接");
			ui.send_btn4->setEnabled(false);
		}
	}

	if (numb == 4)
	{
		if (type == 1)
		{
			ui.status_4->setText("连接");
			ui.send_btn4->setEnabled(true);
		}
		if (type == -1)
		{
			ui.status_4->setText("未连接");
			ui.send_btn4->setEnabled(false);
		}
	}

	if (numb == 5)
	{
		if (type == 1)
		{
			ui.status_5->setText("连接");
			ui.send_btn5->setEnabled(true);
		}
		if (type == -1)
		{
			ui.status_5->setText("未连接");
			ui.send_btn5->setEnabled(false);
		}
	}
}

void MainUi::Socket_Connect_State(int numb, int type)
{
	//断开连接
	if (type == -1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (client_socket[i] == numb)
			{
				client_socket[i] = -1;
				Connet_State_Show(i, -1);
			}
		}
	}

	//建立连接
	if (type == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (client_socket[i] == -1)
			{
				client_socket[i] = numb;
				Connet_State_Show(i, 1);
				break;
			}
		}
	}
}

void MainUi::Send_Content1()
{
	my_listen_thread.Send_Content(ui.textEdit_2->toPlainText(), client_socket[0]);
}
void MainUi::Send_Content2()
{
	my_listen_thread.Send_Content(ui.textEdit_2->toPlainText(), client_socket[1]);
}
void MainUi::Send_Content3()
{
	my_listen_thread.Send_Content(ui.textEdit_2->toPlainText(), client_socket[2]);
}
void MainUi::Send_Content4()
{
	my_listen_thread.Send_Content(ui.textEdit_2->toPlainText(), client_socket[3]);
}
void MainUi::Send_Content5()
{
	my_listen_thread.Send_Content(ui.textEdit_2->toPlainText(), client_socket[3]);
}
void MainUi::Init_Socket_State()
{
	for (int i = 0; i < 5; i++)
	{
		client_socket[i] = -1;
	}
}

MainUi::~MainUi()
{

}

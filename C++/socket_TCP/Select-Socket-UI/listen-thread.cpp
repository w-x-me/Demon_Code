#include"listen-thread.h"
ListenThread::ListenThread()
{

}
ListenThread::~ListenThread()
{

}
void ListenThread::Send_Content(QString content,int socket_number)
{
	for (int i = 0; i < allSockSet.fd_count; i++)
	{
		if (socket_number == allSockSet.fd_array[i])
		{
			char*  ch;
			content.append("\n");
			QByteArray ba = content.toLatin1(); // must
			ch = ba.data();
			int nRet = send(allSockSet.fd_array[i], ch, strlen(ch) + 1, 0);
		}
	}
	//char* buf = Send_Content(bufRecv);
	//int nRet = send(socket, buf, strlen(buf) + 1, 0);
}
void ListenThread::run()
{
	result = WSAStartup(version, &wsaData);
	if (result != 0)
	{
		emit content_signal("WSAStartup() error.");
	}

	/// 创建服务器通行的socket 
	SOCKET socketListen;
	socketListen = socket(AF_INET, SOCK_STREAM, 0);
	if (socketListen == INVALID_SOCKET)
	{
		WSACleanup();
		emit content_signal("socket() error.");
	
	}

	/// 服务器地址结构 
	sockaddr_in svrAddress;
	svrAddress.sin_family = AF_INET;
	char* ip_address;
	QByteArray ba = ip.toLatin1(); // must
	ip_address = ba.data();
	svrAddress.sin_addr.s_addr = inet_addr(ip_address);
	svrAddress.sin_port = htons(port.toInt());

	/// 绑定服务器套接字 
	result = bind(socketListen, (sockaddr*)&svrAddress, sizeof(svrAddress));
	if (result == SOCKET_ERROR)
	{
		closesocket(socketListen);
		WSACleanup();
		emit content_signal("bind() error.");
	
	}

	/// 开启监听
	result = listen(socketListen, 5);
	if (result == SOCKET_ERROR)
	{
		closesocket(socketListen);
		WSACleanup();
		emit content_signal("listen() error.");
		
	}
	emit content_signal("服务器启动成功，监听端口：");

	//FD_CLR(s, *set); 从set集合中删除s套接字。
	//FD_ISSET(s, *set); 检查s是否为set集合的成员。
	//FD_SET(s, *set); 将套接字加入到set集合中。
	//FD_ZERO(*set); 将set集合初始化为空集合。

	// select模型 
	allSockSet;//储存套接字集合结构体
	FD_ZERO(&allSockSet);//初始化套接字结构体


	struct timeval timeout;//select函数等待超时参数
	timeout.tv_sec = 1;//连接超时，单位秒
	timeout.tv_usec = 0;//等待超时，单位毫秒

	FD_SET(socketListen, &allSockSet); // 将socketListen加入套接字集合中 

	while (true)
	{
		fd_set readSet;//创建储存读取消息的结构体
		FD_ZERO(&readSet);
		readSet = allSockSet;
		//参数1：被忽略。传入0即可，参数2：可读套接字集合结构体，参数3：可写套接字集合结构体，参数4：错误套接字集合结构体，参数5：等待超时时间
		result = select(0, &readSet, NULL, NULL, NULL);//检查readSet集合中各个套接字状态是否有改变,没状态变换，就一直等待，有变化就往下执行，修改每个fd_set结构,删除不存在的或没有完成IO操作的套接字。
		if (result == SOCKET_ERROR)
		{
			emit content_signal("listen() error.");
			break;
		}

		if (FD_ISSET(socketListen, &readSet))
		{
			sockaddr_in clientAddr;
			int len = sizeof(clientAddr);

			SOCKET clientSocket = accept(socketListen, (sockaddr*)&clientAddr, &len);//获取申请连接的套接字
			if (clientSocket == INVALID_SOCKET)
			{
				emit content_signal("accept() error.");
				break;
			}
			FD_SET(clientSocket, &allSockSet);// 将新创建的套接字加入到集合中 

			char ipAddress[16] = { 0 };
			inet_ntop(AF_INET, &clientAddr, ipAddress, 16);
			QString content("有新的连接[");
			content.append(ipAddress);
			content.append(":");
			QString port = QString::number(ntohs(clientAddr.sin_port));
			content.append(port);
			content.append("], 目前客户端的数量为：");
			QString fd_counts = QString::number(allSockSet.fd_count - 1);
			content.append(fd_counts);
			emit content_signal(content);
			emit socket_signal(clientSocket,1);
			continue;
		}

		for (u_int i = 0; i < allSockSet.fd_count; ++i)
		{
			SOCKET socket = allSockSet.fd_array[i];

			sockaddr_in clientAddr;
			int len = sizeof(clientAddr);
			getpeername(socket, (struct sockaddr *)&clientAddr, &len);
			char ipAddress[16] = { 0 };
			inet_ntop(AF_INET, &clientAddr, ipAddress, 16);

			/// 可读性监视，可读性指有连接到来、有数据到来、连接已关闭、重置或终止
			if (FD_ISSET(socket, &readSet))
			{
				char bufRecv[100];
				result = recv(socket, bufRecv, 100, 0);
				if (result == SOCKET_ERROR)
				{
					DWORD err = WSAGetLastError();
					if (err == WSAECONNRESET)		/// 客户端的socket没有被正常关闭,即没有调用closesocket
					{
						QString content("客户端[");
						content.append(ipAddress);
						content.append(":");
						QString port = QString::number(ntohs(clientAddr.sin_port));
						content.append(port);
						content.append("]被强行关闭,");
						emit content_signal(content);
						
					}
					else
					{
						emit content_signal("recv() error，");
						std::cout << "recv() error，" << std::endl;
					}

					closesocket(socket);
					FD_CLR(socket, &allSockSet);
					QString content("目前客户端的数量为：");
					
					QString fd_count = QString::number(allSockSet.fd_count - 1);
					content.append(fd_count);
					emit content_signal(content);
					emit socket_signal(socket, -1);
					break;
				}
				else if (result == 0)				/// 客户端的socket调用closesocket正常关闭
				{
					closesocket(socket);
					FD_CLR(socket, &allSockSet);
					allSockSet.fd_array[i] = 0;
					QString content("客户端[");
					content.append(ipAddress);
					content.append(":");

					
					QString port=QString::number( ntohs(clientAddr.sin_port));
					content.append("]已经退出，目前客户端的数量为：");
					QString fd_count = QString::number(allSockSet.fd_count - 1);
					content.append(fd_count);
					emit content_signal(content);
					emit socket_signal(socket, -1);
					break;
				}

				bufRecv[result] = '\0';
				QString content("来自客户端[");
				content.append(ipAddress);
				
				QString port=QString::number(ntohs(clientAddr.sin_port));
				content.append(port);
				content.append("]的消息：");
				content.append(bufRecv);
				emit content_signal(content);

			}
		}
	}

	for (u_int i = 0; i < allSockSet.fd_count; ++i)
	{
		SOCKET socket = allSockSet.fd_array[i];
		closesocket(socket);
	}

	WSACleanup();
}
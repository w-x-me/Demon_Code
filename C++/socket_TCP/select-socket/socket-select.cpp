#define  IP_ADDRESS "192.168.1.133"
#include <WS2tcpip.h>
#include <WinSock2.H>
#include <iostream>
#include <string>
#define FD_SETSIZE 12
#pragma comment(lib, "ws2_32.lib") 
char* Send_Content(char* str)
{
	std::string str1(str);
	if (str1=="11\n")
	{
		return "11\n";
	}
	if (str1 == "22\n")
	{
		return "22\n";
	}
	if (str1 == "33\n")
	{
		return "33\n";
	}
}
int main()
{
	/// 初始化socket
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);
	int result = 0;
	result = WSAStartup(version, &wsaData);
	if (result != 0)
	{
		std::cout << "WSAStartup() error." << std::endl;
		return -1;
	}

	/// 创建服务器通行的socket 
	SOCKET socketListen;
	socketListen = socket(AF_INET, SOCK_STREAM, 0);
	if (socketListen == INVALID_SOCKET)
	{
		WSACleanup();
		std::cout << "socket() error." << std::endl;
		return -1;
	}

	/// 服务器地址结构 
	sockaddr_in svrAddress;
	svrAddress.sin_family = AF_INET;
	svrAddress.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	svrAddress.sin_port = htons(8002);

	/// 绑定服务器套接字 
	result = bind(socketListen, (sockaddr*)&svrAddress, sizeof(svrAddress));
	if (result == SOCKET_ERROR)
	{
		closesocket(socketListen);
		WSACleanup();
		std::cout << "bind() error." << std::endl;
		return -1;
	}

	/// 开启监听
	result = listen(socketListen, 5);
	if (result == SOCKET_ERROR)
	{
		closesocket(socketListen);
		WSACleanup();
		std::cout << "listen() error." << std::endl;
		return -1;
	}
	std::cout << "服务器启动成功，监听端口：" << ntohs(svrAddress.sin_port) << std::endl;
	
	//FD_CLR(s, *set); 从set集合中删除s套接字。
	//FD_ISSET(s, *set); 检查s是否为set集合的成员。
	//FD_SET(s, *set); 将套接字加入到set集合中。
	//FD_ZERO(*set); 将set集合初始化为空集合。
	
	// select模型 
	fd_set allSockSet;//储存套接字集合结构体
	allSockSet.fd_count = 3;//设置监控
	FD_ZERO(&allSockSet);//初始化套接字结构体
	

	struct timeval timeout;//select函数等待超时参数
	timeout.tv_sec = 0;//连接超时，单位秒
	timeout.tv_usec = 100;//等待超时，单位毫秒

	FD_SET(socketListen, &allSockSet); // 将socketListen加入套接字集合中 

	while (true)
	{
		fd_set readSet;//创建储存读取消息的结构体
		readSet.fd_count = 3;
		FD_ZERO(&readSet);
		
		readSet = allSockSet;
		//参数1：被忽略。传入0即可，参数2：可读套接字集合结构体，参数3：可写套接字集合结构体，参数4：错误套接字集合结构体，参数5：等待超时时间
		result = select(0, &readSet, NULL, NULL, &timeout);//检查readSet集合中各个套接字状态是否有改变,没状态变换，就一直等待，有变化就往下执行，修改每个fd_set结构,删除不存在的或没有完成IO操作的套接字。
		if (result == SOCKET_ERROR)
		{
			std::cout << "listen() error." << std::endl;
			break;
		}

		if (FD_ISSET(socketListen, &readSet))
		{
			sockaddr_in clientAddr;
			int len = sizeof(clientAddr);

			SOCKET clientSocket = accept(socketListen, (sockaddr*)&clientAddr, &len);//获取申请连接的套接字
			if (clientSocket == INVALID_SOCKET)
			{
				std::cout << "accept() error." << std::endl;
				break;
			}
			FD_SET(clientSocket, &allSockSet);	 /// 将新创建的套接字加入到集合中 

			char ipAddress[16] = { 0 };
			inet_ntop(AF_INET, &clientAddr, ipAddress, 16);
			std::cout << "有新的连接[" << ipAddress << ":" << ntohs(clientAddr.sin_port)
				<< "], 目前客户端的数量为：" << allSockSet.fd_count - 1 << std::endl;

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
						std::cout << "客户端[" << ipAddress << ":" << ntohs(clientAddr.sin_port) << "]被强行关闭, ";
					}
					else
					{
						std::cout << "recv() error，" << std::endl;
					}

					closesocket(socket);
					FD_CLR(socket, &allSockSet);

					std::cout << "目前客户端的数量为：" << allSockSet.fd_count - 1 << std::endl;
					break;
				}
				else if (result == 0)				/// 客户端的socket调用closesocket正常关闭
				{
					closesocket(socket);
					FD_CLR(socket, &allSockSet);

					std::cout << "客户端[" << ipAddress << ":" << ntohs(clientAddr.sin_port)
						<< "]已经退出，目前客户端的数量为：" << allSockSet.fd_count - 1 << std::endl;
					break;
				}

				bufRecv[result] = '\0';
				std::cout << "来自客户端[" << ipAddress << ":" << ntohs(clientAddr.sin_port)
					<< "]的消息：" << bufRecv << std::endl;
				char* buf = Send_Content(bufRecv);
				int nRet = send(socket, buf, strlen(buf) + 1, 0);

			}
		}
	}

	for (u_int i = 0; i < allSockSet.fd_count; ++i)
	{
		SOCKET socket = allSockSet.fd_array[i];
		closesocket(socket);
	}

	WSACleanup();
	return 0;
}
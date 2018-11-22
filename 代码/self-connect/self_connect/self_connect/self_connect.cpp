// self_connect.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>

#pragma comment(lib, "WS2_32.lib")

void ConnectServer(char *ip_addr, int port)
{
	//创建SOCKET
	SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET)
	{
		WSACleanup();
		printf("创建套接字失败\n");
		return;
	}

	//连接服务端
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = inet_addr(ip_addr);
	addrServer.sin_port = htons(port);

	int test_count = 65536;
	while (test_count--)
	{
		if (connect(sClient, (SOCKADDR*)&addrServer, sizeof(addrServer)) != SOCKET_ERROR)
		{
			printf("连接服务器成功\n");
			closesocket(sClient);
			break;
		}
	}

	WSACleanup();
}

int main()
{
	WSADATA VersionData;
	WSAStartup(MAKEWORD(2, 2), &VersionData);

	ConnectServer("127.0.0.1", 55555);
    return 0;
}


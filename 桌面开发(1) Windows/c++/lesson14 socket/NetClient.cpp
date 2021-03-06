// Windows Socket Application
#include <stdio.h>
#include <Winsock2.h>	// 项目需要链接 ws2_32.lib 库

void main()
{
	WORD	wVersionRequested;
	WSADATA	wsaData;
	int		err;

	// 加载 WinSock.dll 套接字库, 进行套接字库的版本协商
	// 参数: 版本号, WSADATA 结构体指针
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return;
	}
	if (   LOBYTE(wsaData.wVersion) != 1
		|| HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return;
	}


	SOCKET		sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN	addrServer;
	char		recvBuf[100];
	char		sendBuf[100];
	char		tempBuf[200];
	int			len = sizeof(SOCKADDR);

	addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);

	while (1)
	{
		// 发送数据给服务器
		printf("I say: ");
		gets(sendBuf);
		sendto(sockClient, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR *)&addrServer, len);

		// 从服务器接收数据
		recvfrom(sockClient, recvBuf, 100, 0, (SOCKADDR *)&addrServer, &len);
		if ('q' == recvBuf[0])
		{
			sendto(sockClient, "q", strlen("q") + 1, 0, (SOCKADDR *)&addrServer, len);
			printf("Char Ended!");
			break;
		}
		sprintf(tempBuf, "%s says: %s", inet_ntoa(addrServer.sin_addr), recvBuf);
		printf("%s\n", tempBuf);
	}
	closesocket(sockClient);
	WSACleanup();
}
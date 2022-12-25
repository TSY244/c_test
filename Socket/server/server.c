#include"../tcpSocket/tcpSocket.h"


int main()
{
	init_Socket();
	//函数的调用，创建socket
	SOCKET serfd = CreateServerSocket();
	printf("wait clifd connecnt ...\n");
	//如果有客户端请求连接
	SOCKET clifd=accept(serfd, NULL, NULL);
	if (INVALID_SOCKET == clifd)
	{
		My_error("accept");
	}

	printf("be connected successfully\n");
	//可以和客户端通信

	char sendbuf[BUFSIZ] = { 0 };
	char recvbuf[BUFSIZ] = { 0 };
	while (true)
	{
		if (0 < recv(clifd, recvbuf, BUFSIZ, 0))
		{
			printf("recv:%s\n", recvbuf);
			memset(recvbuf, 0, sizeof(recvbuf));
		}
		//发送信息
		printf("发送信息:");
		//gets_s(sendbuf, BUFSIZ);
		gets(sendbuf);
		if (SOCKET_ERROR == send(clifd, sendbuf, strlen(sendbuf), 0))
		{
			My_error("send");
		}
		memset(sendbuf, 0, sizeof(sendbuf));
	}



	closesocket(clifd);
	closesocket(serfd);


	close_Socket();
	printf("---------server_end---------");
	getchar();
	return 0;
}
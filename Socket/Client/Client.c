#include "../tcpSocket/tcpSocket.h"
#include <windows.h>
int main()
{
	init_Socket();
	//�����ͻ��˵�socket
	//SOCKET fd=CreateClientSocket("127.0.0.1");
	SOCKET fd = CreateClientSocket();
	//����Ϣ��������
	char recvbuf[BUFSIZ] = { 0 };
	char sendbuf[BUFSIZ] = { 0 };
	char change[BUFSIZ] = { 0 };
	printf("be connected successfully\n");
	while (true)
	{
		//������Ϣ
		printf("������Ϣ:");
		//gets_s(sendbuf, BUFSIZ);
		gets(sendbuf);
		if (SOCKET_ERROR == send(fd, sendbuf, strlen(sendbuf), 0))
		{
			My_error("send");
		}
		memset(sendbuf, 0, sizeof(sendbuf));
		if (0 < recv(fd, recvbuf, BUFSIZ, 0))
		{
			printf("recv:%s\n", recvbuf);
			memset(recvbuf, 0, sizeof(recvbuf));
		}
	}
	closesocket(fd);
	close_Socket();
	printf("---------Client_end---------");
	return 0;
}


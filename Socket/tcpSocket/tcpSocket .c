#include "tcpSocket.h"


//�������
bool init_Socket()
{
	LPWSADATA Open_WSA;
	if (0 != WSAStartup(MAKEWORD(2, 3), &Open_WSA))
	{
		My_error("WSAStartup");
		return false;
	}
	return true;
}
//�ر������
bool close_Socket()
{
	if (0 != WSACleanup())
	{
		My_error("WSACleanup");
		return false;
	}
	return true;
}

SOCKET CreateServerSocket()
{
	// 1.�����յ�Socket
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)
	{
		My_error("socket");
		return  INVALID_SOCKET;
	}
	// 2.��socket��ip��ַ�Ͷ˿�
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;//����˿ڱ�����ǰ��һ��
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = ADDR_ANY;
	if (SOCKET_ERROR == bind(fd, (struct sockaddr*)&addr, sizeof(addr)))
	{
		My_error("bind");
		return false;
	}
	//����
	listen(fd, 10);
	return fd;
}

SOCKET CreateClientSocket()//(const char* ip)
{
	
	// 1.�����յ�Socket
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)
	{
		My_error("socket");
		return  INVALID_SOCKET;
	}
	// 2.�����������
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;//����˿ڱ�����ǰ��һ��
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
	if (INVALID_SOCKET == connect(fd, (struct sockaddr*)&addr, sizeof(addr)))
	{
		My_error("connect");
		return false;
	}
	return fd;
}

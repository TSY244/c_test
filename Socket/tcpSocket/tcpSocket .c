#include "tcpSocket.h"


//打开网络库
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
//关闭网络库
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
	// 1.创建空的Socket
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)
	{
		My_error("socket");
		return  INVALID_SOCKET;
	}
	// 2.给socket绑定ip地址和端口
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;//这里端口必须与前面一致
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = ADDR_ANY;
	if (SOCKET_ERROR == bind(fd, (struct sockaddr*)&addr, sizeof(addr)))
	{
		My_error("bind");
		return false;
	}
	//监听
	listen(fd, 10);
	return fd;
}

SOCKET CreateClientSocket()//(const char* ip)
{
	
	// 1.创建空的Socket
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)
	{
		My_error("socket");
		return  INVALID_SOCKET;
	}
	// 2.与服务器建立
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;//这里端口必须与前面一致
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
	if (INVALID_SOCKET == connect(fd, (struct sockaddr*)&addr, sizeof(addr)))
	{
		My_error("connect");
		return false;
	}
	return fd;
}

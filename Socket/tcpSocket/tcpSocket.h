#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H_
//#define _CRT_SECURE_NO_WARNINGS 1
//#define _WINSOCK_DEPRECATED_NO_WARNINGS



//ͷ�ļ�
#include<WinSock2.h> 
#pragma comment(lib,"ws2_32.lib")
#include<stdbool.h>
#include<stdio.h>

//�궨��
#define My_error(Error) printf("[ Line: %d ] %s failed code %d",__LINE__,Error,WSAGetLastError());
#define PORT 8888  //[0--65536] 0--1024 �Ǳ����˿ڣ�����ʹ�ã����ò�Ҫʹ��1000��  

//�������
bool init_Socket();
//�ر������
bool close_Socket();
//����������socket
SOCKET CreateServerSocket();
//�����ͻ��˵�socket
SOCKET CreateClientSocket();//(const char* ip);

 
#endif 
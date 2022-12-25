#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H_
//#define _CRT_SECURE_NO_WARNINGS 1
//#define _WINSOCK_DEPRECATED_NO_WARNINGS



//头文件
#include<WinSock2.h> 
#pragma comment(lib,"ws2_32.lib")
#include<stdbool.h>
#include<stdio.h>

//宏定义
#define My_error(Error) printf("[ Line: %d ] %s failed code %d",__LINE__,Error,WSAGetLastError());
#define PORT 8888  //[0--65536] 0--1024 是保留端口，不能使用，做好不要使用1000的  

//打开网络库
bool init_Socket();
//关闭网络库
bool close_Socket();
//创建服务器socket
SOCKET CreateServerSocket();
//创建客户端的socket
SOCKET CreateClientSocket();//(const char* ip);

 
#endif 
/*************************************************************************
 * File Name: server.c
 * Author: unite
 * Tel: 18758077967
 * Created Time: 2023年07月12日 星期三 19时38分05秒
 ************************************************************************/
#include <stdbool.h>
#include "server.h"
#include "sockapi.h"   //initServer  acceptClient
#include "multitask.h" //createPthread
#include "log.h"	   //LOG 宏函数

void serverRun(const char *ip, unsigned short port)
{
	// 1.初始化网络   tcp服务器  (1.socket  2.bind  3.listen)
	int sockfd = initServer(ip, port); // 拿到socket的 file descriptor
	if (sockfd == -1)
	{
		LOG("初始化服务器失败!\n");
		return;
	}
	// 2.循环等待客户端连接
	while (true)
	{										 // 典中典while循环
		int clientfd = acceptClient(sockfd); // 拿到此次会话的file descriptor
		if (clientfd == -1)
		{
			LOG("处理客户端连接时失败!\n");
			continue;
		}
		// 3.有客户端连接上来  创建线程为该客户端服务
		int ret = createPthread(clientfd);
		if (ret == -1)
		{
			LOG("创建线程失败!\n");
		}
	}
}

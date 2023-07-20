/*************************************************************************
 * File Name: multitask.c
 * Author: unite
 * Tel: 18758077967
 * Created Time: 2023年07月12日 星期三 20时47分33秒
 ************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "multitask.h"
#include "sockapi.h" //recvRequet   sendResponse
#include "route.h"	 //routeEntry
#include "log.h"

void *handleClient(void *arg)
{									  // 返回一个void* 指针
	int clientfd = *(int *)arg;		  // 绷，指针强转
	LOG("clientfd = %d\n", clientfd); //  LOG 函数是调试信息输出  logger
	while (true)
	{
		// 接收客户端的请求包
		void *request = NULL;
		// 接收一个请求 分配内存空间用于存储 请求的数据
		int ret = recvRequest(clientfd, &request); // 去让request指向一个动态内存的地址
		if (ret == -1)
		{
			close(clientfd);
			break;
		}
		// 解析请求包 用户需要干什么(去调用对应的函数)
		void *response = NULL;
		// 业务程序的入口  程序处理之后 分配内存 把返回给用户的数据放到内存中
		ret = routeEntry(request, &response);
		// 给用户回一个响应(应答)包
		sendResponse(clientfd, response, ret + 4);
		if (request != NULL)
		{
			free(request); // malloc 然后 free 释放内存 捏麻我记得要把 request这个指针置空来着，哦对了这里确实不用置空，反正它是临时变量
		}
		if (response != NULL)
		{
			free(response);
		}
	}
	return NULL;
}

int createPthread(int clientfd)
{
	pthread_t id;
	static int fd;
	fd = clientfd;
	LOG("create:%d\n", clientfd);
	// 这个是 pthread  process thread 的创建方法， 邵忠包含一个 会话的file descriptor 还有一个处理函数
	int ret = pthread_create(&id, NULL, handleClient, &fd); // 保证传过去的地址有效  然后id会被赋值

	if (ret != 0)
	{ // 典中典之异常处理
		printf("pthread_create:%s\n", strerror(ret));
		return -1;
	}
	return 0;
}

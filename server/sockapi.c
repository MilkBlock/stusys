/*************************************************************************
 * File Name: sockapi.c
 * Author: unite
 * Tel: 18758077967
 * Created Time: 2023年07月12日 星期三 20时32分14秒
 ************************************************************************/
#include <string.h> //strerror  能够通过一个错误码获取错误码所对应的错误信息
#include <errno.h>	//全局变量  extern int errno;
#include <stdlib.h>
#include "sockapi.h"
#include "log.h"

#define MAX_PENDING_CNT 100
// 标准C语言和linux操作系统的函数调用接口 出错 都会设置全局的errno  （线程库pthread不会设置全局的ernno,线程库中的函数出错直接返回错误码，成功返回0）

int initServer(const char *ip, unsigned short port)
{ // 这里是用ip初始化服务器
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		LOG("socket:%s\n", strerror(errno));
		return -1;
	}
	struct sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	// setsockopt
	int ret = 0;
	ret = bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
	if (ret == -1)
	{
		LOG("bind:%s\n", strerror(errno));
		return -1;
	}

	ret = listen(sockfd, MAX_PENDING_CNT);
	if (ret == -1)
	{
		LOG("listen:%s\n", strerror(errno));
		return -1;
	}
	return sockfd;
}

int acceptClient(int sockfd)
{
	struct sockaddr_in addr = {};
	socklen_t len = sizeof(addr);
	int cfd = accept(sockfd, (struct sockaddr *)&addr, &len); // 在这里服务器有一次拒绝连接的机会
	if (cfd == -1)
	{
		LOG("accept:%s\n", strerror(errno));
		return -1;
	}
	LOG("%s:%hu 客户端连接到服务器!\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	printf("client:%d\n", cfd);
	return cfd;
}

int recvRequest(int sockfd, void **request) // 返回包体的位置
{
	unsigned int size = 0;								// 首先读取4字节   包体的大小
	ssize_t ret = recv(sockfd, &size, sizeof(size), 0); // 严格读取4个字节
	if (ret <= 0)
	{
		LOG("recv:%s\n", strerror(errno));
		return -1;
	}
	*request = malloc(size - sizeof(size));
	if (*request == NULL)
	{
		LOG("malloc:%s\n", strerror(errno));
		return -1;
	}
	ret = recv(sockfd, *request, size - sizeof(size), 0);
	if (ret <= 0)
	{
		LOG("recv:%s\n", strerror(errno));
		return -1;
	}
	return 0;
}

int sendResponse(int sockfd, void *response, int len)
{												  // 纯度极高的sendResponse
	ssize_t ret = send(sockfd, response, len, 0); // write 和 send 语义好像差不多，只是 socket file descriptor 必须要用 send
	// 而对于普通的文件需要用  write
	if (ret <= 0)
	{
		LOG("send:%s\n", strerror(errno));
		return -1;
	}
	return 0;
}

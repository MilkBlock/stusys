/*************************************************************************
 * File Name: sockapi.c
 * Author: unite
 * Tel: 18758077967
 * Created Time: 2023年07月13日 星期四 01时45分54秒
 ************************************************************************/
#include <string.h>
#include "sockapi.h"

int connectServer(const char *ip, unsigned short port)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	int ret = connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
	if (ret == -1)
	{
		perror("connect");
		return -1;
	}
	return sockfd;
}

int sendRequest(int sockfd, int dowhat, void *request, size_t size)
{ // 这个size 是专指 request 的 size
	int s = size + 4 + 4;
	send(sockfd, &s, sizeof(int), 0);
	send(sockfd, &dowhat, sizeof(int), 0);
	send(sockfd, request, size, 0);
	return 0;
}

int recvResponse(int sockfd, void *response, size_t size)
{
	int s = 0;
	recv(sockfd, &s, sizeof(int), 0);
	recv(sockfd, response, size, 0);
	return 0;
}

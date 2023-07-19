/*************************************************************************
	* File Name: sockapi.h
	* Author: unite
	* Tel: 18758077967 
	* Created Time: 2023年07月12日 星期三 20时30分46秒
 ************************************************************************/
#ifndef _SOCK_API_H__
#define _SOCK_API_H__

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int initServer(const char *ip,unsigned short port);
int acceptClient(int sockfd);
int recvRequest(int sockfd,void **request);
int sendResponse(int sockfd,void *reponse,int len);

#endif //_SOCK_API_H__

/*************************************************************************
	* File Name: sockapi.h
	* Author: unite
	* Tel: 18758077967 
	* Created Time: 2023年07月13日 星期四 01时41分57秒
 ************************************************************************/
#ifndef _SOCK_API_H__
#define _SOCK_API_H__

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int connectServer(const char *ip,unsigned short port);
int sendRequest(int sockfd,int dowhat,void *request,size_t size);
int recvResponse(int sockfd,void *response,size_t size);

#endif //_SOCK_API_H__

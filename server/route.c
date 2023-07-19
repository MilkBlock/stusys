/*************************************************************************
 * File Name: route.c
 * Author: unite
 * Tel: 18758077967
 * Created Time: 2023年07月12日 星期三 23时31分57秒
 ************************************************************************/
#include "route.h"
#include "stusys.h"

// 典中典 寻路
struct Route routes[] = {
	{LOGIN, login}, // 一个 Route struct 由两个变量组成，一个是标识符，另一个是函数的地址
	{ADD, add},
	{DEL, del},
	{MOD, mod},
	{FIND, find},
	{LIST, list}};

int routeEntry(void *request, void **response)
{
	// request 前面4byte 要干什么
	//  绷， do what
	int dowhat = *(int *)request;
	int i;
	for (i = 0; i < sizeof(routes) / sizeof(routes[0]); i++)
	{
		if (routes[i].dowhat == dowhat)
		{
			return routes[i].func(request + sizeof(dowhat), response);
		}
	}
	return -1;
}

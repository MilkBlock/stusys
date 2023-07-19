/*************************************************************************
 * File Name: route.h
 * Author: unite
 * Tel: 18758077967
 * Created Time: 2023年07月12日 星期三 23时28分40秒
 ************************************************************************/
#ifndef _ROUTE_H__
#define _ROUTE_H__

#include <stdio.h>
#include <stdlib.h>
#include "stusys.h"

typedef int (*FUNC)(void *data, void **response);

struct Route
{ // 我擦，这个居然是写在.h文件里的
	int dowhat;
	FUNC func;
};

int routeEntry(void *request, void **response); // 寻路 找到客户端请求的operation

#endif //_ROUTE_H__

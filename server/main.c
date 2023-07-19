/*************************************************************************
 * File Name: main.c
 * Author: unite
 * Tel: 18758077967
 * Created Time: 2023年07月12日 星期三 19时26分32秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "server.h"

int main(int argc, char *argv[])
{
	// 启动服务器   ip   port          配置文件 从命令行启动时传入
	if (argc < 3)
	{ // two args are required  两个参数
		printf("用法:\n");
		printf("\t %s server_ip server_port\n", argv[0]); // 启动格式
		return -1;
	}
	// ip: argv[1]  port: argv[2]
	serverRun(argv[1], atoi(argv[2])); // 服务器入口

	return 0;
}

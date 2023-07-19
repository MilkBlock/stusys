/*************************************************************************
	* File Name: main.c
	* Author: unite
	* Tel: 18758077967 
	* Created Time: 2023年07月13日 星期四 01时15分54秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "client.h"

int main(int argc,char *argv[]){
	if(argc < 3){
		printf("用法:\n");
		printf("\t %s server_ip server_port\n",argv[0]);
		return -1;
	}

	clientRun(argv[1],atoi(argv[2]));
    
	return 0;
}

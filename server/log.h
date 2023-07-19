/*************************************************************************
	* File Name: log.h
	* Author: unite
	* Tel: 18758077967 
	* Created Time: 2023年07月12日 星期三 19时49分37秒
 ************************************************************************/
#ifndef _LOG_H__
#define _LOG_H__

#include <stdio.h>

//日志  记录程序运行的信息
//      日志分级别   按信息的重要程序  critical/fatal  error  warning  info  debgu

#define LOG(fmt,args...) \
	printf("[%s:%d] "fmt,__FILE__,__LINE__,##args)


#endif //_LOG_H__

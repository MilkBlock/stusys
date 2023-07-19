/*************************************************************************
 * File Name: stusys.c
 * Author: unite
 * Tel: 18758077967
 * Created Time: 2023年07月13日 星期四 00时16分44秒
 ************************************************************************/
#include <string.h>
#include "stusys.h"
#include "log.h"

int makeResponse(void *data, int size, void **response)
{
	*response = malloc(size + 4);
	if (*response == NULL)
	{
		return -1;
	}
	*(int *)(*response) = size + 4;
	memcpy(*response + 4, data, size);
	return 0;
}

int login(void *data, void **response)
{ // login 操作的函数 是帮我们写好了 好好好大抄特抄
	struct Login *plogin = (struct Login *)data;
	LOG("userno:%d, role:%s, password:%s\n", plogin->userno, plogin->role == MANAGER ? "管理员" : "学生", plogin->passwd);
	int retsize = 0;
	if (plogin->role == MANAGER)
	{
		struct ManagerLoginRet ret = {SUCCESS};
		retsize = sizeof(ret);
		makeResponse(&ret, sizeof(ret), response);
	}
	else
	{																								  //
		struct StudentLoginRet ret = {SUCCESS, {20230001, "张三", "男", 18, {90, 91, 99}, "123456"}}; // 绷，居然是个常量struct
		ret.stu.no = plogin->userno;
		strcpy(ret.stu.passwd, plogin->passwd);
		makeResponse(&ret, sizeof(ret), response); // 返回个张三
		retsize = sizeof(ret);
	}
	return retsize;
}

int add(void *data, void **response)
{
}

int del(void *data, void **response)
{
}

int find(void *data, void **response)
{
}

int list(void *data, void **response)
{
}

int mod(void *data, void **response)
{
}

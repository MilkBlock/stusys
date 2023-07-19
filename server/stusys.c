/*************************************************************************
 * File Name: stusys.c
 * Author: unite
 * Tel: 18758077967
 * Created Time: 2023年07月13日 星期四 00时16分44秒
 ************************************************************************/
#include <string.h>
#include "stusys.h"
#include "log.h"
#include "sockapi.h"

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
{
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

// 学生上限是一千把那就
struct Stu students[1000];
int students_n = 1; // 最开始只有张三一个学生
int add(void *data, void **response)
{
	struct OptRet ret;
	memcpy(students + students_n, data, sizeof(struct Stu));

	ret.isSuccessful = 1;
	const char *tmp = "成功 add 力";
	strcpy(ret.char_info, tmp);
	makeResponse(&ret, sizeof(struct OptRet), response);
}

int del(void *data, void **response)
{
	struct OptRet ret;
	if (students_n == 0)
	{
		ret.isSuccessful = 0;
		const char *tmp = "students 已经没货了";
		strcpy(ret.char_info, tmp);
		makeResponse(&ret, sizeof(struct OptRet), response);
		return
		// 报错删无可删
	}
	// first find it
	int find_stu_index;
	for (int i = 0; i < students_n; i++)
	{
		if (students[i].no == ((*Stu)(data)).no)
		{
			find_stu_index = i;
			break;
		}
	}

	// 删除之后移位
	for (int i = find_stu_index + 1; i < students_n; i++)
	{
		memcpy(students + i - 1, students + i, sizof(struct Stu));
	}
	students_n -= 1;

	ret.isSuccessful = 1;
	const char *tmp = "students 成功减员";
	strcpy(ret.char_info, tmp);
	makeResponse(&ret, sizeof(struct OptRet), response);
}

int find(void *data, void **response)
{
	struct OptRet ret;
	int find_stu_index = -1;
	for (int i = 0; i < students_n; i++)
	{
		if (students[i].no == ((*Stu)(data)).no)
		{
			find_stu_index = i;
			break;
		}
	}
	// if not found
	if (find_stu_index == -1)
	{
		ret.isSuccessful = 0;
		const char *tmp = "诶，没找到";
		strcpy(ret.char_info, tmp);
		makeResponse(&ret, sizeof(struct OptRet), response);
	} // if found it
	else
	{
		ret.isSuccessful = 1;
		const char *tmp = "我擦，找到了";
		strcpy(ret.char_info, tmp);

		memcpy(&ret.stu, &students[find_stu_index], sizeof(struct Stu)); // 取成员运算是最高优先级 比 & 优先了

		makeResponse(&ret, sizeof(struct OptRet), response);
	}
}

int list(void *data, void **response)
{
	makeResponse(students, sizeof(struct Stu) * students_n, response);
}

int mod(void *data, void **response)
{
	// makeResponse(data, sizeof(data), response)
	// 	sendResponse(data, ) // sockfd response len
	// first find it
	struct OptRet ret;
	int find_stu_index = -1;
	for (int i = 0; i < students_n; i++)
	{
		if (students[i].no == ((*Stu)(data)).no)
		{
			find_stu_index = i;
			break;
		}
	}
	if (find_stu_index == -1)
	{
		ret.isSuccessful = 0;
		const char *tmp = "诶，没找到，这没法改啊";
		strcpy(ret.char_info, tmp);
		makeResponse(&ret, sizeof(struct OptRet), response);
	}
	else
	{
		memcpy(&students[find_stu_index], &ret.stu, sizeof(struct Stu)); // 取成员运算是最高优先级 比 & 优先了
		makeResponse(&ret, sizeof(struct OptRet) + (students_n - 1) * sizeof(struct Stu), response);
	}
}

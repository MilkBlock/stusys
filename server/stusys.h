/*************************************************************************
 * File Name: stusys.h
 * Author: unite
 * Tel: 18758077967
 * Created Time: 2023年07月13日 星期四 00时12分43秒
 ************************************************************************/
#ifndef _STU_SYS_H__
#define _STU_SYS_H__
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

enum OPER
{
	LOGIN = 9527,
	ADD,
	DEL,
	FIND,
	LIST,
	MOD
}; // operations ，检测用户请求的是哪一种操作
enum ROLE
{
	MANAGER,
	STUDENT
}; // 应该是作为status 中的数据

#define PASS_LEN 16
#define NAME_LEN 64
#define SEX_LEN 8
#define SCORE_CNT 3

int login(void *data, void **response);
int add(void *data, void **response);
int del(void *data, void **response);
int find(void *data, void **response);
int list(void *data, void **response);
int mod(void *data, void **response);

void initStus();

struct Stu
{ // 学生properties 真多啊，挺能爆金币的吧
	int no;
	char name[NAME_LEN];
	char sex[SEX_LEN]; // 绷  gender 写成 sex
	int age;
	int score[SCORE_CNT];
	char passwd[PASS_LEN];
};

struct Login
{
	int userno;			   // user 的编号吧
	int role;			   // MANAGER  STU      俩选项  Manager 还有 student  MANAGER STU
	char passwd[PASS_LEN]; // 这是一次登录的请求，因此需要输入密码
};

struct ManagerLoginRet
{
	int stat; // SUCCESS FAILURE     应该是作为返回的response
};
struct StudentLoginRet
{
	int stat;
	struct Stu stu; // 顺带返回一些学生的基础信息？
};

// 操作是否成功以及相应提示的response结构体
struct OptRet
{
	int isSuccessful;
	char char_info[20];
	struct Stu stu;
};

#endif //_STU_SYS_H__

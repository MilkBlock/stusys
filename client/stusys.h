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
};
enum ROLE
{
	MANAGER,
	STUDENT
};

#define PASS_LEN 16
#define NAME_LEN 64
#define SEX_LEN 8
#define SCORE_CNT 3

struct Stu
{
	int no;
	char name[NAME_LEN];
	char sex[SEX_LEN];
	int age;
	int score[SCORE_CNT];
	char passwd[PASS_LEN];
};

struct Login
{
	int userno;
	int role; // MANAGER  STU
	char passwd[PASS_LEN];
};

struct ManagerLoginRet
{
	int stat; // SUCCESS FAILURE
};

struct StudentLoginRet
{
	int stat;
	struct Stu stu;
};
struct OptRet
{
	bool isSuccessful;
	char[20] char_info;
	struct Stu stu;
};
#endif //_STU_SYS_H__

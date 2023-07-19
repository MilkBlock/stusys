/*************************************************************************
 * File Name: client.c
 * Author: unite
 * Tel: 18758077967
 * Created Time: 2023年07月13日 星期四 01时19分31秒
 ************************************************************************/
#include <stdbool.h>
#include "client.h"
#include "stusys.h"
#include "password.h"
#include "sockapi.h"

void unLoginMenu(void)
{
	printf("**********xx学生信息管理系统*************\n");
	printf("***  1.管理员登录 \n");
	printf("***  2.学生登录   \n");
	printf("***  0.退出系统   \n");
	printf(">>>");
}

void managerMenu(void)
{
	printf("*******学生信息管理系统(管理员界面)*******\n");
	printf(" 0.退出\n");
	printf(" 1.录入学生\n");
	printf(" 2.删除学生\n");
	printf(" 3.修改学生信息\n");
	printf(" 4.查找学生\n");
	printf(" 5.列出学生\n");
	printf(">>");
}

void stuMenu(void)
{
	printf("*******学生信息管理系统(学生界面)********\n");
	printf(" 0.退出\n");
	printf(" 1.查看个人信息\n");
	printf(" 2.修改密码\n");
	printf(">>");
}

void addStu(void)
{
	printf("doing ...   add student!\n");
}

void delStu(void)
{
	printf("doing ....  del student!\n");
}

void modStu(void)
{
	printf("doing ....  mod student!\n");
}

void listStu(void)
{
	printf("doing ... list student!\n");
}

void findStu(void)
{
	printf("doing  ... find student!\n");
}

void modStuPass(struct Stu *ps)
{
	printf("doing  ... mod student password!\n");

	sendRequest()
}

void managerSysRun(void)
{
	while (true)
	{
		managerMenu();
		int in = 0;
		scanf("%d", &in);
		// 调用不同的函数
		if (in == 0)
		{
			return;
		}
		if (in == 1)
		{
			addStu();
		}
		else if (in == 2)
		{
			delStu();
		}
		else if (in == 3)
		{
			modStu();
		}
		else if (in == 4)
		{
			findStu();
		}
		else if (in == 5)
		{
			listStu();
		}
		else
		{
			printf("Error\n");
		}
	}
}

void stuSysRun(struct Stu *ps)
{
	while (true)
	{
		stuMenu();
		int in = 0;
		scanf("%d", &in);
		if (in == 0)
		{
			return;
		}
		else if (in == 1)
		{
			printf("\t学号:%d\n", ps->no);
			printf("\t姓名:%s\n", ps->name);
			printf("\t性别:%s\n", ps->sex);
			printf("\t年龄:%d\n", ps->age);
			printf("\t成绩:");
			int i;
			for (i = 0; i < SCORE_CNT; i++)
			{
				printf("%d ", ps->score[i]);
			}
			printf("\n");
		}
		else if (in == 2)
		{
			// 修改密码　　　学号　旧密码　新密码　　发送给服务器　　去接收服务器响应
			modStuPass(ps);
		}
	}
}

void clientRun(const char *ip, unsigned short port)
{
	bool islogin = false;
	int role = 0;
	struct Stu stu = {}; // 学生登录时 保存学生的信息
	while (true)
	{
		if (!islogin)
		{ // 没有登录
			unLoginMenu();
			int in = 0;
			scanf("%d", &in);
			if (in == 0)
			{
				return; // 退出
			}
			if (in != 1 && in != 2)
			{
				printf("Error!\n");
				continue;
			}
			struct Login login = {};
			login.role = in == 1 ? MANAGER : STUDENT;
			role = login.role;
			printf("请输入用户名:");
			scanf("%d", &login.userno);
			printf("请输入密码:");
			getpasswd(login.passwd, PASS_LEN);

			// 连接服务器  把数据发给服务器  接收服务器响应
			int sockfd = connectServer(ip, port);
			if (sockfd == -1)
			{
				printf("服务器已宕机!\n");
				return;
			}

			sendRequest(sockfd, LOGIN, &login, sizeof(login));
			if (in == 1)
			{
				struct ManagerLoginRet ret = {};
				recvResponse(sockfd, &ret, sizeof(ret));
				if (ret.stat == SUCCESS)
				{
					islogin = true;
				}
				else
				{
					printf("用户名或者密码错误!\n");
				}
			}
			else
			{
				struct StudentLoginRet ret = {};
				recvResponse(sockfd, &ret, sizeof(ret));
				if (ret.stat == SUCCESS)
				{
					islogin = true;
					printf("no:%d\n", ret.stu.no);
					printf("name:%s\n", ret.stu.name);
					printf("sex:%s\n", ret.stu.sex);
					printf("age:%d\n", ret.stu.age);
					printf("score:%d %d %d\n", ret.stu.score[0], ret.stu.score[1], ret.stu.score[2]);
					printf("passwd:%s\n", ret.stu.passwd);
					stu = ret.stu;
				}
				else
				{
					printf("用户名或者密码错误!\n");
				}
			}
			close(sockfd);
		}
		else
		{ // 已经登录
			if (role == MANAGER)
			{
				managerSysRun(); // 管理员登录之后的操作
			}
			else
			{
				stuSysRun(&stu); // 学生登录之后的操作
			}
			islogin = false;
		}
	}
}

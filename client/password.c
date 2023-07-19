#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

//函数set_disp_mode用于控制是否开启输入回显功能
//如果option为0，则关闭回显，为1则打开回显
#define DEL 127

int set_disp_mode(int fd,int option){
	int err;
	struct termios term;
	if(tcgetattr(fd,&term)==-1){
		perror("Cannot get the attribution of the terminal");
		return 1;
	}
	if(option)
		term.c_lflag|=(ICANON | ECHO);
	else
        term.c_lflag &=~(ICANON | ECHO);
	err=tcsetattr(fd,TCSAFLUSH,&term);
	if(err==-1 && err==EINTR){
        perror("Cannot set the attribution of the terminal");
        return 1;
	}
	return 0;
}

//函数getpasswd用于获得用户输入的密码，并将其存储在指定的字符数组中
int getpasswd(char* passwd, int size){
   	set_disp_mode(STDIN_FILENO,0);//设置输入的内容不会显示出来
	int c;
	int n = 0; 
	do{
		c = getchar();
      	if(c == DEL){//Backspace
			if(n>0){//删除之前输入的一个字符 删除了一个*
				printf("\b");//退格
				printf(" ");//覆盖后面的*
				printf("\b");//退格
				passwd[--n] = '\0';//把存储的真正的字符删除
	  			fflush(stdout);
			}
	  	}else if (c != '\n' && c!='\r'){
         	passwd[n++] = c;
		 	printf("*");//只要不是换行，输入一个字符就用*来替换
	     	fflush(stdout);
      	}
   	}while((c != '\n' && c !='\r' && n < (size - 1)) || n==0);
  	passwd[n] = '\0';
   	set_disp_mode(STDIN_FILENO,1);//恢复回显
	printf("\n");
   	return n;
}


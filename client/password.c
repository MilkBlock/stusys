#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

//����set_disp_mode���ڿ����Ƿ���������Թ���
//���optionΪ0����رջ��ԣ�Ϊ1��򿪻���
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

//����getpasswd���ڻ���û���������룬������洢��ָ�����ַ�������
int getpasswd(char* passwd, int size){
   	set_disp_mode(STDIN_FILENO,0);//������������ݲ�����ʾ����
	int c;
	int n = 0; 
	do{
		c = getchar();
      	if(c == DEL){//Backspace
			if(n>0){//ɾ��֮ǰ�����һ���ַ� ɾ����һ��*
				printf("\b");//�˸�
				printf(" ");//���Ǻ����*
				printf("\b");//�˸�
				passwd[--n] = '\0';//�Ѵ洢���������ַ�ɾ��
	  			fflush(stdout);
			}
	  	}else if (c != '\n' && c!='\r'){
         	passwd[n++] = c;
		 	printf("*");//ֻҪ���ǻ��У�����һ���ַ�����*���滻
	     	fflush(stdout);
      	}
   	}while((c != '\n' && c !='\r' && n < (size - 1)) || n==0);
  	passwd[n] = '\0';
   	set_disp_mode(STDIN_FILENO,1);//�ָ�����
	printf("\n");
   	return n;
}


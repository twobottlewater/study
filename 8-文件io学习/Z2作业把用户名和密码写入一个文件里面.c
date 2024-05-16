#include "myhead.h"





int main()
{
	//定义用户名变量密码变量和buf存储
	char name[20];
	char passwd[20];
	char buf[20];
	int fd;
	
	//打开一个文件
	fd=open("msg.txt",O_RDWR|O_APPEND);
	if(fd==-1)
	{
		printf("打开文件失败了\n");
		return -1;
		
		}
		
	while(1)
	{
		bzero(name,20);
		bzero(passwd,20);
		bzero(buf,30);
		printf("请你输一个注册名字\n");
		scanf("%s",name);
		if(strcmp(name,"quit")==0)
			break;
		printf("请输入密码\n");
		scanf("%s",passwd);
		//字符串合并
		sprintf(buf,"%s@%s\n",name,passwd);
		
		//把拼接的字符串写入到文件中
		write(fd,buf,strlen(buf));
		
		}
	return 0;	
}
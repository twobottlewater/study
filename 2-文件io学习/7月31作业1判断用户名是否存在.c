#include "myhead.h"
/*
	作业1：判断用户名是否存在
	
*/
int main(int argc,char **argv)
{
	int fd;
	//定义数组存放输入的用户名和密码
	char name[20]={0};
	char passwd[20]={0};
	//定义数组存放拼接后的结果
	char msg[100]={0};
	FILE *myfile;
	char *p;

lb:	
	bzero(name,20);
	bzero(passwd,20);
	printf("请输入您要注册的用户名和密码!\n");
	scanf("%s",name);
	scanf("%s",passwd);

	//打开源文件
	myfile=fopen("msg.txt","r+");  //可读写
	if(myfile==NULL)
	{
		printf("打开文件失败了!\n");
		return -1;
	}
	//一行行读取文件内容，判断用户名是否存在
	while(1)
	{
		bzero(msg,100);
		fgets(msg,100,myfile);
		if(feof(myfile)) //文件读取完毕
			break;
		printf("读取的内容是: %s\n",msg);
		//切割字符串
		p=strtok(msg,"@"); //p存放的就是用户名
		//判断用户名是否存在
		if(strcmp(p,name)==0) //用户名存在
		{
			printf("对不起，您注册的用户名已经被占用!\n");
			fclose(myfile);
			goto lb;
		}
		
	}
	
	//把新的用户名和密码写入到文件中
	//拼接字符串
	bzero(msg,100);
	sprintf(msg,"%s@%s\n",name,passwd);
	printf("%s\n",msg);
	fwrite(msg,strlen(msg),1,myfile);
	
	//关闭文件
	fclose(myfile);
	return 0;
}
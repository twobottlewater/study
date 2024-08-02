#include "myhead.h"

/*
	多线程实现tcp双向通信
	客户端或者服务器任意一方输入quit结束程序
*/
int sockfd;

//线程的任务函数--》专门接收服务器回复的信息
void *myrecvmsg(void *arg)
{
	char rbuf[100];
	int ret;
	while(1)
	{
		bzero(rbuf,100);
		//接收服务器回复的信息
		ret=recv(sockfd,rbuf,100,0);
		if(ret==0) //说明服务器断开了(退出了)
		{
			printf("服务器挂掉了!\n");
			exit(0); //结束整个进程
		}
		printf("服务器给我回复的信息是: %s\n",rbuf);
	}
}
int main(int argc,char **argv)
{
	int ret;
	//定义变量保存线程的ID
	pthread_t id;
	//定义数组存放要发送的字符串
	char sbuf[100];
	
	//定义ipv4地址结构体变量保存你要绑定的ip和端口号(绑定本地主机自己的ip和端口号)
	struct sockaddr_in bindaddr;
	bzero(&bindaddr,sizeof(bindaddr));
	bindaddr.sin_family=AF_INET;
	//偷懒的，不需要写具体ip
	bindaddr.sin_addr.s_addr=htonl(INADDR_ANY);  //INADDR_ANY宏定义可以匹配当前ubuntu上任意ip地址
	bindaddr.sin_port=htons(atoi(argv[1]));
	
	//定义ipv4地址结构体变量保存对方(服务器)的ip和端口号
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr("192.168.7.3");  //服务器的ip地址
	serveraddr.sin_port=htons(atoi(argv[2])); //服务器的端口号
	
	//创建tcp套接字--》买手机
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("创建tcp套接字失败了!\n");
		return -1;
	}
		
	//绑定ip和端口号
	ret=bind(sockfd,(struct sockaddr *)&bindaddr,sizeof(bindaddr));
	if(ret==-1)
	{
		perror("绑定ip和端口号失败了!\n");
		return -1;
	}
	
	//连接服务器
	ret=connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(ret==-1)
	{
		perror("连接服务器失败了!\n");
		return -1;
	}
	
	//创建一个线程专门用来接收服务器回复的信息
	pthread_create(&id,NULL,myrecvmsg,NULL);
	
	//主函数专门从键盘输入字符串发送给服务器
	while(1)
	{
		bzero(sbuf,100);
		printf("张三请输入要发送给服务器的信息!\n");
		scanf("%s",sbuf);
		//发送给服务器--》两种方法
		//write(sockfd,sbuf,strlen(sbuf));
		send(sockfd,sbuf,strlen(sbuf),0);
	}
	
	//关闭套接字
	close(sockfd);
	return 0;
}
#include "myhead.h"

/*
	tcp，ubuntu作为客户端跟阿里云通信
	阿里云上的代码
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
	bindaddr.sin_port=htons(10086);
	
	//定义ipv4地址结构体变量保存对方(服务器)的ip和端口号
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr("8.138.126.11");  //阿里云服务器的ip地址(公网ip)
	serveraddr.sin_port=htons(10000); //服务器的端口号
	
	//创建tcp套接字--》买手机
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("创建tcp套接字失败了!\n");
		return -1;
	}
	
	//只能写在此位置，设置端口复用
	int on=1;  //非零值
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
		
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
		if(strcmp(sbuf,"quit")==0)
			exit(0); //客户端退出断掉了
		//发送给服务器--》两种方法
		//write(sockfd,sbuf,strlen(sbuf));
		send(sockfd,sbuf,strlen(sbuf),0);
	}
	
	//关闭套接字
	close(sockfd);
	return 0;
}
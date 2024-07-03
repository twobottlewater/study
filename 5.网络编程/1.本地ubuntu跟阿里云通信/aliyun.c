#include "myhead.h"

/*
	tcp，ubuntu作为客户端跟阿里云通信
	阿里云上的代码
*/
//定义变量保存accept函数返回的新套接字
int newsock;
//线程的任务函数--》专门发送信息给客户端
void *mysendmsg(void *arg)
{
	char sbuf[100];
	while(1)
	{
		bzero(sbuf,100);
		printf("请输入要回复给客户端的信息!\n");
		scanf("%s",sbuf);
		if(strcmp(sbuf,"quit")==0)
			exit(0); //服务器退出断掉了
		send(newsock,sbuf,strlen(sbuf),0);
	}
}
int main(int argc,char **argv)
{
	int sockfd;
	int ret;
	pthread_t id;
	//定义数组存放要接收的字符串
	char rbuf[100];
	
	//定义ipv4地址结构体变量保存你要绑定的ip和端口号(绑定本地主机自己的ip和端口号)
	struct sockaddr_in bindaddr;
	bzero(&bindaddr,sizeof(bindaddr));
	bindaddr.sin_family=AF_INET;
	//偷懒的，不需要写具体ip
	bindaddr.sin_addr.s_addr=htonl(INADDR_ANY);  //INADDR_ANY宏定义可以匹配当前ubuntu上任意ip地址
	bindaddr.sin_port=htons(10000); //服务器自己的端口号
	
	//定义ipv4地址结构体变量保存对方(客户端)的ip和端口号
	struct sockaddr_in clientaddr;
	bzero(&clientaddr,sizeof(clientaddr));
	int addrsize=sizeof(clientaddr);
	
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
	
	//监听
	ret=listen(sockfd,10); //最多允许10个客户端同时连接同一个服务器
	if(ret==-1)
	{
		perror("监听失败了!\n");
		return -1;
	}
	
	//接受客户端的连接请求，产生新的套接字用来跟该客户端通信
	newsock=accept(sockfd,(struct sockaddr *)&clientaddr,&addrsize);
	if(newsock==-1)
	{
		perror("接受客户端的连接失败!\n");
		return -1;
	}		
	
	//创建一个线程专门发送信息给客户端
	pthread_create(&id,NULL,mysendmsg,NULL);
	
	//主函数专门接收客户端发送过来的信息
	while(1)
	{
		bzero(rbuf,100);
		ret=recv(newsock,rbuf,100,0);
		if(ret==0) //说明客户端挂了
		{
			printf("客户端挂掉了!\n");
			exit(0); //结束进程
		}
		printf("客户端给我发送的信息是: %s\n",rbuf);
	}
	
	//关闭套接字
	close(sockfd);
	close(newsock);
	return 0;
}
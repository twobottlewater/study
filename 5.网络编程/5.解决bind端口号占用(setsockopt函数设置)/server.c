#include "myhead.h"

/*
	tcp双向通信
	服务器的代码
*/
int newsock;
void *mysendmsg(void *arg)
{
	char sbuf[100];
	while(1)
	{
		bzero(sbuf,100);
		printf("请输入要回复给客户端的信息!\n");
		scanf("%s",sbuf);
		send(newsock,sbuf,strlen(sbuf),0);
	}
}
int main()
{
	int tcpsock;
	int ret;
	char rbuf[100];
	pthread_t id;
	//定义ipv4地址结构体变量
	struct sockaddr_in bindaddr;
	bzero(&bindaddr,sizeof(bindaddr));
	bindaddr.sin_family=AF_INET; //地址协议
	bindaddr.sin_addr.s_addr=inet_addr("192.168.60.60"); //服务器自己的ip
	bindaddr.sin_port=htons(10086);  //服务器的端口号
	
	//定义ipv4地址结构体变量存放连接成功客户端的ip和端口号
	struct sockaddr_in clientaddr;
	int size=sizeof(clientaddr);
	
	//创建tcp套接字 --》买手机
	tcpsock=socket(AF_INET,SOCK_STREAM,0);
	if(tcpsock==-1)
	{
		perror("创建tcp套接字失败了!\n");
		return -1;
	}
	
	//取消端口绑定限制
	int on=1; //非零
	setsockopt(tcpsock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	
	//绑定ip和端口号 --》绑定手机号
	ret=bind(tcpsock,(struct sockaddr *)&bindaddr,sizeof(bindaddr));
	if(ret==-1)
	{
		perror("绑定ip和端口号失败了!\n");
		return -1;
	}
	
	//监听 --》待机
	ret=listen(tcpsock,6);
	if(ret==-1)
	{
		perror("监听失败!\n");
		return -1;
	}
	
	//接收客户端的连接请求 --》愿意接听 
	bzero(&clientaddr,sizeof(clientaddr));
	newsock=accept(tcpsock,(struct sockaddr *)&clientaddr,&size);
	if(newsock==-1)
	{
		perror("接收客户端的连接请求失败!\n");
		return -1;
	}
	
	//创建一个线程专门发送信息
	pthread_create(&id,NULL,mysendmsg,NULL);
	
	//接收客户端发送过来的信息
	while(1)
	{
		bzero(rbuf,100);
		recv(newsock,rbuf,100,0);
		printf("服务器收到的信息是: %s\n",rbuf);
	}
	
	//关闭套接字
	close(tcpsock);
	return 0;
}
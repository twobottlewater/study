#include "myhead.h"

/*
	htonl(INADDR_ANY);  //INADDR_ANY宏定义可以匹配当前ubuntu上任意ip地址
	好处：各位同学在绑定的时候就不需要写死ip地址
	缺点：INADDR_ANY宏定义只能在绑定的时候使用，其他地方(比如:connect)不能使用
*/

int main()
{
	int sockfd;
	int ret;
	//定义数组存放要发送的字符串
	char sbuf[100];
	
	//定义ipv4地址结构体变量保存你要绑定的ip和端口号(绑定本地主机自己的ip和端口号)
	struct sockaddr_in bindaddr;
	bzero(&bindaddr,sizeof(bindaddr));
	bindaddr.sin_family=AF_INET;
	bindaddr.sin_addr.s_addr=htonl(INADDR_ANY);  //INADDR_ANY宏定义可以匹配当前ubuntu上任意ip地址
	bindaddr.sin_port=htons(10086);
	
	//定义ipv4地址结构体变量保存对方(服务器)的ip和端口号
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr("192.168.1.20");  //服务器的ip地址
	serveraddr.sin_port=htons(10000); //服务器的端口号
	
	//创建tcp套接字--》买手机
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("创建tcp套接字失败了!\n");
		return -1;
	}
	
	printf("目前客户端套接字文件描述符是: %d\n",sockfd);
	
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
	
	//从键盘输入字符串发送给服务器
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
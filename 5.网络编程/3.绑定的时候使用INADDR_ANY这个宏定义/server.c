#include "myhead.h"

/*
	htonl(INADDR_ANY);  //INADDR_ANY宏定义可以匹配当前ubuntu上任意ip地址
	好处：各位同学在绑定的时候就不需要写死ip地址
	缺点：INADDR_ANY宏定义只能在绑定的时候使用，其他地方(比如:connect)不能使用
*/

int main()
{
	int sockfd;
	//定义变量保存accept函数返回的新套接字
	int newsock;
	int ret;
	//定义数组存放要接收的字符串
	char rbuf[100];
	
	//定义ipv4地址结构体变量保存你要绑定的ip和端口号(绑定本地主机自己的ip和端口号)
	struct sockaddr_in bindaddr;
	bzero(&bindaddr,sizeof(bindaddr));
	bindaddr.sin_family=AF_INET;
	bindaddr.sin_addr.s_addr=htonl(INADDR_ANY); 
	//INADDR_ANY宏定义可以匹配当前ubuntu上任意ip地址
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
	
	printf("目前服务器端旧的套接字文件描述符是: %d\n",sockfd);
	
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
	
	//把accept按在地上摩擦哦，让它一直不停地接收不同客户端的连接请求
	while(1)
	{
		printf("服务器确实阻塞在accept的前面了!\n");
		//接受客户端的连接请求，产生新的套接字用来跟该客户端通信
		newsock=accept(sockfd,(struct sockaddr *)&clientaddr,&addrsize);
		if(newsock==-1)
		{
			perror("接受客户端的连接失败!\n");
			return -1;
		}		
		printf("目前连接成功的客户端ip地址是：%s  端口号是: %hu\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
		printf("有个客户端连接服务器成功了，服务器产生了新的套接字是: %d\n",newsock);
	}
	
	
	
	
	//关闭套接字
	close(sockfd);
	close(newsock);
	return 0;
}
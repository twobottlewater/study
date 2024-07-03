#include "myhead.h"

/*
	udp双向通信
*/
int udpsock;
void *myrecvmsg(void *arg)
{
	char rbuf[100];
	int ret;
	struct sockaddr_in addr;
	int size=sizeof(addr);
	while(1)
	{
		bzero(rbuf,100);
		//ret=recvfrom(udpsock,rbuf,100,0,NULL,NULL); //表示我只想接收信息，我不关心究竟是谁发给我的
		ret=recvfrom(udpsock,rbuf,100,0,(struct sockaddr *)&addr,&size); //表示接收信息，同时把发送信息的那个主机的信息存储
		printf("服务器给我发送的信息是: %s recvfrom返回值跟recv是不一样的 %d\n",rbuf,ret);
	}
	pthread_exit(NULL);
}

int main()
{
	int ret;
	char sbuf[100];
	pthread_t id;
	
	//定义ipv4地址结构体变量
	struct sockaddr_in bindaddr;
	bzero(&bindaddr,sizeof(bindaddr));
	bindaddr.sin_family=AF_INET; //地址协议
	bindaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	bindaddr.sin_port=htons(10086); 
	
	//定义ipv4地址结构体变量存放对方的ip和端口号
	struct sockaddr_in otheraddr;
	bzero(&otheraddr,sizeof(otheraddr));
	otheraddr.sin_family=AF_INET;
	otheraddr.sin_addr.s_addr=inet_addr("127.0.0.1"); //对方的ip地址
	otheraddr.sin_port=htons(5548);  //对方的端口号
	
	//创建udp套接字
	udpsock=socket(AF_INET,SOCK_DGRAM,0);
	if(udpsock==-1)
	{
		perror("创建udp套接字失败了!\n");
		return -1;
	}
	
	//取消端口绑定限制
	int on=1; //非零
	setsockopt(udpsock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	
	//绑定ip和端口号 
	ret=bind(udpsock,(struct sockaddr *)&bindaddr,sizeof(bindaddr));
	if(ret==-1)
	{
		perror("绑定ip和端口号失败了!\n");
		return -1;
	}
	
	//创建一个线程专门接收信息
	pthread_create(&id,NULL,myrecvmsg,NULL);
	
	//发送信息
	while(1)
	{
		bzero(sbuf,100);
		printf("请输入要发送的信息!\n");
		scanf("%s",sbuf);
		//发送出去
		sendto(udpsock,sbuf,strlen(sbuf),0,(struct sockaddr *)&otheraddr,sizeof(otheraddr));
	}
	
	//关闭套接字
	close(udpsock);
	return 0;
}
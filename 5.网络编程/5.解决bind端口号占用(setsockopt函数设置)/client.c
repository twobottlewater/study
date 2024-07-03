#include "myhead.h"

/*
	tcp双向通信
	客户端的代码
*/
int tcpsock;
void *myrecvmsg(void *arg)
{
	char rbuf[100];
	while(1)
	{
		bzero(rbuf,100);
		recv(tcpsock,rbuf,100,0);
		printf("服务器给我发送的信息是: %s\n",rbuf);
	}
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
	//错误：ubuntu采用小端序存放数据，直接写ip，就是小端序，需要转换成大端序
	//bindaddr.sin_addr.s_addr="192.168.60.60"; //老师强调了，绑定客户端自己的ip
	//正确：
	bindaddr.sin_addr.s_addr=inet_addr("192.168.60.60");
	bindaddr.sin_port=htons(5548);  //客户端端口号
	
	//定义ipv4地址结构体变量存放服务器的ip和端口号
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr("192.168.60.60"); //服务器的ip地址
	serveraddr.sin_port=htons(10086);  //服务器端口号
	
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
	
	//连接服务器 --》拨号
	ret=connect(tcpsock,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(ret==-1)
	{
		perror("连接服务器失败了!\n");
		return -1;
	}
	
	//创建一个线程专门接收信息
	pthread_create(&id,NULL,myrecvmsg,NULL);
	
	//发送信息给服务器
	while(1)
	{
		bzero(sbuf,100);
		printf("请输入要发送给服务器的信息!\n");
		scanf("%s",sbuf);
		//发送出去
		send(tcpsock,sbuf,strlen(sbuf),0);
	}
	
	//关闭套接字
	close(tcpsock);
	return 0;
}
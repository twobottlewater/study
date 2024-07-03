#include "myhead.h"
#include "kernel_list.h"


/*
	多个客户端连接同一个服务器
	服务器研究如下几个问题
	    1.accept是阻塞的，如果有客户端连接服务器成功，accept就解除阻塞，产生新套接字
		2.accept每个客户端连接都产生新的不同的套接字
		3.accept第二个参数自动保存连接成功的客户端信息
*/

int sockfd;

//定义结构体存放连接成功的客服端信息
struct clientinfo
{
	int sock;//放套接字
	char ipbuf[20];//放ip地址
	unsigned short portnum;
	//指针域
	struct list_head mypoint;

};



//初始化头节点
struct clientinfo* init_list()
{
	struct clientinfo  *head=malloc(sizeof(struct clientinfo));
	INIT_LIST_HEAD(&(head->mypoint));
	return head;	
}

//定义一个接收客服端的信息函数
void* myrecv_msg(void *arg)	
{
	struct clientinfo *temp=(struct clientinfo*)arg;
	char buf[110];
	while (1)
	{
		recv(temp->sock,buf,100,0);
		printf("客户端%s  %hu 说:%s\n",temp->ipbuf,temp->portnum,buf);
	}
	

}


int main()
{
	
	//定义变量保存accept函数返回的新套接字
	int newsock;
	int ret;
	//定义数组存放要接收的字符串
	char rbuf[100];
	
	//定义ipv4地址结构体变量保存你要绑定的ip和端口号(绑定本地主机自己的ip和端口号)
	struct sockaddr_in bindaddr;
	bzero(&bindaddr,sizeof(bindaddr));
	bindaddr.sin_family=AF_INET;
	bindaddr.sin_addr.s_addr=inet_addr("192.168.1.20");  //服务器自己的ip地址
	bindaddr.sin_port=htons(10000); //服务器自己的端口号
	
	//定义ipv4地址结构体变量保存对方(客户端)的ip和端口号
	struct sockaddr_in clientaddr;
	bzero(&clientaddr,sizeof(clientaddr));
	int addrsize=sizeof(clientaddr);
	
	//初始化内核链表的头结点
	struct clientinfo *myhead=init_list();

	

	//创建tcp套接字--》买手机
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("创建tcp套接字失败了!\n");
		return -1;
	}
	
	
	int on=1;
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
	


	//创建一个线程用来接收不同客服端的信息
	pthread_t tid;
	
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
		struct clientinfo *newnode=malloc(sizeof(struct clientinfo));
		newnode->sock=newsock;
		strcpy(newnode->ipbuf,inet_ntoa(clientaddr.sin_addr));
		newnode->portnum=ntohs(clientaddr.sin_port);
		INIT_LIST_HEAD(&(newnode->mypoint));

		//立马把这个客服端的信息保存到内核链表里面
		list_add_tail(&newnode->mypoint,&myhead->mypoint);

		pthread_create(&tid,NULL,myrecv_msg,newnode);
	}
	
	
	
	
	//关闭套接字
	close(sockfd);
	close(newsock);
	return 0;
}
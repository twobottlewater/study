#include "myhead.h"

/*
	1.基于消息队列的通信方式实现一个服务器/客户端模式系统：
	（1）	s服务端从消息队列读取需要计算的两个整数，求和后把结果通过消息队列返回c客户端；
	（2）	c客户端从键盘读取两个整数，通过消息队列发送s服务器，接收到s服务器的计算结果后显示出来
	（3）	要求服务端能同时处理多个客户端的请求(1:n)
         创建三个进程，p1当成服务器，p2和p3作为客户端
         p1  p2  p3

*/

//自定义一个结构体，存放你要发送的信息和信息类型
struct mymsg
{
	//消息类型--》彭老师图上的那个数字
	long type;
	//消息内容
	int num1;
	int num2;
	int n;   //表示不同客户端  1是第一个客服端  2是第二个客户端

};

int msgid;
void fun()
{
	//删除消息队列
	msgctl(msgid,IPC_RMID,NULL);
}

int main()
{
	signal(SIGINT,fun);
	
	key_t mykey=ftok("/home",4);
	//申请打开消息队列
	msgid=msgget(mykey,IPC_CREAT|IPC_EXCL|0777);
	if(msgid==-1)
	{
		if(errno==EEXIST)
		{
			msgid=msgget(mykey,0777);
		}
		else
		{
			perror("申请/打开消息队列失败!\n");
			return -1;
		}
		
		
	}	
	
	struct mymsg rmsg;
	int result;
	/*
	while(1)
	{
		bzero(&rmsg,sizeof(rmsg));
		msgrcv(msgid,&rmsg,12,100,0);
		printf("服务器收到的数据：%d  %d 该数据是第%d个客服端发送过来的\n",rmsg.num1,rmsg.num2,rmsg.n);
		
	}
	*/
	while(1)
	{
		bzero(&rmsg,sizeof(rmsg));
		msgrcv(msgid,&rmsg,12,100,0);
		result=rmsg.num1+rmsg.num2;
		rmsg.num1=result;
		//判断是那个客服端发来的数据
		if(rmsg.n==1)
		{
			rmsg.type=80;
			msgsnd(msgid,&rmsg,12,0);
		}
		if(rmsg.n==2)
		{
			rmsg.type=8080;
			msgsnd(msgid,&rmsg,12,0);
		}
		
	}
	
	

	
	
}
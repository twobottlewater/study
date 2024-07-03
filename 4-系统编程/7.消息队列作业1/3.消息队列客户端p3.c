#include "myhead.h"

/*
	p1通过消息队列发送三条信息给p2
*/

//自定义一个结构体，存放你要发送的信息和信息类型
struct mymsg
{
	//消息类型--》彭老师图上的那个数字
	long type;
	//消息内容
	int num1;
	int num2;
	int n;
};


int main()
{
	int msgid;
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
	//定义一个结构体保存住数据
	struct mymsg msg2;
	//请输入两个整数
	while(1)
	{
	  bzero(&msg2,sizeof(msg2));//先清空再使用
	  printf("请输入两个整数\n");
	  scanf("%d",&(msg2.num1));
      scanf("%d",&(msg2.num2));
	  msg2.n=2;
	  msg2.type=100;//消息类型
	  msgsnd(msgid,&msg2,12,0);
	  
	  printf("发送数据成功，请等待结果\n");
	  	  //接受数据的函数
	  bzero(&msg2,sizeof(msg2));//先清空再使用
	  msgrcv(msgid,&msg2,12,8080,0);
	  printf("计算的结果是：%d\n",msg2.num1);
	}
	
	

	
	
	
	

	
	
	
}
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
	char mbuf[100]; 
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
	//接收信息
	//ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);
	struct mymsg rmsg;
	bzero(&rmsg,sizeof(rmsg));
	msgrcv(msgid,&rmsg,sizeof(rmsg),965,0);
	printf("我收到的信息是: %s\n",rmsg.mbuf);
	
	bzero(&rmsg,sizeof(rmsg));
	msgrcv(msgid,&rmsg,sizeof(rmsg),147,0);
	printf("我收到的信息是: %s\n",rmsg.mbuf);
	
	bzero(&rmsg,sizeof(rmsg));
	msgrcv(msgid,&rmsg,sizeof(rmsg),458,0);
	printf("我收到的信息是: %s\n",rmsg.mbuf);
	
	
	
}
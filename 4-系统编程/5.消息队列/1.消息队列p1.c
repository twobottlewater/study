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
	//利用消息队列发送、接收信息
	struct mymsg msg1;
	bzero(&msg1,sizeof(msg1));
	msg1.type=458;
	strcpy(msg1.mbuf,"hello");
	msgsnd(msgid,&msg1,sizeof(msg1),0);
	
	struct mymsg msg2;
	bzero(&msg2,sizeof(msg2));
	msg2.type=965;
	strcpy(msg2.mbuf,"gec");
	msgsnd(msgid,&msg2,sizeof(msg2),0);
	
	struct mymsg msg3;
	bzero(&msg3,sizeof(msg3));
	msg3.type=147;
	strcpy(msg3.mbuf,"China");
	msgsnd(msgid,&msg3,sizeof(msg3),0);
	
	
	
}
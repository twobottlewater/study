#include "myhead.h"

int main()
{
	//第一步：申请共享内存
	int shmid;  
	shmid=shmget(4557,1024,IPC_CREAT|IPC_EXCL|0777);
	if(shmid==-1)
	{
		if(errno==EEXIST) //共享内存已经申请过了
		{
			//打开共享内存
			shmid=shmget(4557,1024,0777);
		}
		else
		{
			perror("申请共享内存失败了!\n");
			return -1;
		}
		
	}
	
	//第二步：通过ID号映射得到共享内存的首地址
	char *p=shmat(shmid,NULL,0);
	if(p==NULL)
	{
		perror("映射共享内存失败了!\n");
	}
	
	//从刚才的首地址中去获取内容
	while(1)
	{
		printf("共享内存里面存放的是: %s\n",p);
	}
	
}
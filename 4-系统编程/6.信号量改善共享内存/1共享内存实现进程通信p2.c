#include "myhead.h"

int main()
{
	
	int semid;
	struct sembuf sem1;
	bzero(&sem1,sizeof(sem1));
	sem1.sem_num=1;   //我要操作第二个信号量
	sem1.sem_op=-1;   //P操作，减1
	sem1.sem_flg=SEM_UNDO; //PV操作之后，还原值
	
	struct sembuf sem2;
	bzero(&sem2,sizeof(sem2));
	sem2.sem_num=0;   //我要操作第一个信号量
	sem2.sem_op=1;   //V操作，加1
	sem2.sem_flg=SEM_UNDO; //PV操作之后，还原值
	
	//第一步：申请两个信号量
	semid=semget(4789,2,IPC_CREAT|IPC_EXCL|0777);
	if(semid==-1)
	{
		if(errno==EEXIST)
		{
			semid=semget(4789,2,0777);
		}
		else
		{
			perror("申请/打开信号量失败了!\n");
			return -1;
		}
	}
	
	
	
	//第二步：申请共享内存
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
	
	//第3步：通过ID号映射得到共享内存的首地址
	char *p=shmat(shmid,NULL,0);
	if(p==NULL)
	{
		perror("映射共享内存失败了!\n");
	}
	
	//从刚才的首地址中去获取内容
	while(1)
	{
		//阻塞进程p2(让p2对第二个信号进行p操作)，让它先不要打印
		semop(semid,&sem1,1);
		printf("共享内存里面存放的是: %s\n",p);
		//对第一个信号量v操作，拯救p1
		semop(semid,&sem2,1);
	}
	
}
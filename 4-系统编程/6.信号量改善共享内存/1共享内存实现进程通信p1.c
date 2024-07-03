#include "myhead.h"

/*
	p1键盘输入字符串，通过共享内存给到p2
	思考观察有什么诡异的现象，如何解决？踩踩坑
*/
char *p;
int shmid;
void fun(int sig)
{
	printf("执行了删除代码!\n");
	//第三步：解除映射
	shmdt(p);
	
	//第四步：删除共享内存
	shmctl(shmid,IPC_RMID,NULL);
	exit(0); //结束进程
}
int main()
{
	//第一步：申请共享内存
	/*
		参数1：键值，两种写法
		       写法1：程序员自己随便指定一个整数
	    参数2：共享内存大小，512的整数倍
		参数3：共享内存的权限
		       IPC_CREAT  //新建、新申请共享内存
			   IPC_EXCL   //如果共享内存已经申请过，再次申请就失败退出
			   0777 
		共享内存已经申请过，不能再次重新申请，只能打开
	*/
	
	signal(SIGINT,fun);
	
	
	int semid;
	struct sembuf sem1;
	bzero(&sem1,sizeof(sem1));
	sem1.sem_num=1;   //我要操作第二个信号量
	sem1.sem_op=1;   //V操作，加1
	sem1.sem_flg=SEM_UNDO; //PV操作之后，还原值
	
	struct sembuf sem2;
	bzero(&sem2,sizeof(sem2));
	sem2.sem_num=0;   //我要操作第一个信号量
	sem2.sem_op=-1;   //P操作，减1
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
	
	//第二步：给刚才申请的两个信号量设置值 
	semctl(semid,0,SETVAL,1); //给序号是0(第一个信号量)的信号量设置值为1
	semctl(semid,1,SETVAL,0); //给序号是1(第二个信号量)的信号量设置值为0
	
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
	printf("申请的共享内存ID是: %d\n",shmid);
	
	//第三步获取共享内存
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
	printf("申请的共享内存ID是: %d\n",shmid);
	
	//第四步：通过ID号映射得到共享内存的首地址
	p=shmat(shmid,NULL,0);
	if(p==NULL)
	{
		perror("映射共享内存失败了!\n");
	}
	
	//利用首地址来存放、取出数据
	while(1)
	{
		//对第一个信号量p操作
		semop(semid,&sem2,1);
		printf("请输入要发送给p2的信息!\n");
		scanf("%s",p);
		//拯救p2，p2一直阻塞在对第二个信号量p操作那里了，对第二个信号量进行V操作
		semop(semid,&sem1,1);
	}
	return 0;
}
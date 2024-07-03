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
	
	//第二步：通过ID号映射得到共享内存的首地址
	p=shmat(shmid,NULL,0);
	if(p==NULL)
	{
		perror("映射共享内存失败了!\n");
	}
	
	//利用首地址来存放、取出数据
	while(1)
	{
		printf("请输入要发送给p2的信息!\n");
		scanf("%s",p);
	}
	return 0;
}
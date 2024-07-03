#include "myhead.h"

/*
	shmctl获取共享内存的属性
	
*/


int main()
{
	char *p;
	int shmid;

	//第一步：申请/打开共享内存
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
	p=shmat(shmid,NULL,0);
	if(p==NULL)
	{
		perror("映射共享内存失败了!\n");
	}
	
	//获取当前申请的这个共享内存的属性信息
	struct shmid_ds myds;
	shmctl(shmid,IPC_STAT,&myds);
	printf("共享内存的大小是： %lu\n",myds.shm_segsz);
	printf("共享内存的键值是： %d\n",myds.shm_perm.__key);
	printf("共享内存的键值是： %#o\n",myds.shm_perm.mode);
	return 0;
}
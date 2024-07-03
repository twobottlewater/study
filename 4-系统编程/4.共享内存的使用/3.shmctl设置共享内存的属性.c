#include "myhead.h"

/*
	shmctl设置共享内存的属性
	
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
	
	//改变/设置当前申请的这个共享内存的属性信息
	struct shmid_ds myds;
	myds.shm_perm.mode=0777; //修改权限，可以修改
	myds.shm_segsz=2048; //修改大小,无法修改
	myds.shm_perm.__key=7894; //修改键值，无法修改
	shmctl(shmid,IPC_SET,&myds);
	
	return 0;
}
#include "myhead.h"

/*
	完整演示进程退出与回收
*/

int main()
{
	pid_t id;
	int i;
	int status;
	printf("父进程运行起来了!\n");
	//创建一个子进程出来
	id=fork();
	if(id>0) //父进程
	{
		printf("父进程的ID： %d\n",getpid());
		printf("父进程执行hello gec,我儿子的ID是: %d\n",id);
	}
	else if(id==0) //子进程
	{
		printf("子进程的ID是: %d\n",getpid());
		/* while(1)
		{
			printf("子进程执行hello world!\n");
			sleep(1);
		}	 */
		exit(5); //退出子进程
	}
	else
	{
		perror("创建子进程失败了!\n");
		return -1;
	}
	printf("父进程准备退出了!\n");
	for(i=0; i<10; i++)
		printf("父进程结束!\n");
	
	//回收刚才新建的子进程
	pid_t ret=wait(&status);
	//判断子进程是正常退出还是异常退出
	if(WIFEXITED(status))
	{
		printf("我的仔是正常退出的,退出值是: %d!\n",WEXITSTATUS(status));
		printf("%d\n",status);
	}
	else
		printf("我的仔是异常退出的!\n");
	printf("父进程回收子进程成功,我回收的子进程ID是: %d\n",ret);
	return 0;
}
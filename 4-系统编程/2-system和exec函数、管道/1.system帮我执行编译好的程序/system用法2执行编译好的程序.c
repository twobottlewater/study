#include "myhead.h"

/*
	system执行另外一个进程(编译好的程序)
	实现在一个进程中调用执行另外一个进程
*/

int main()
{
	/*
		system调用执行另外一个独立的进程分为两种情况
		   情况1：hello里面有死循环，会影响你当前进程后面的代码执行
		          解决方法1：让hello在后台执行，后台执行不会影响到后续的代码
				  解决方法2：借助今天学习fork函数，搞个子进程出来，通过子进程执行system
	*/
	//方法1：让hello在后台执行，后台执行不会影响到后续的代码
	//system("./hello &");  //&符号的意思是后台执行hello
	
	// for(;;)
	// {
		// printf("main main main，我的ID： %d\n",getpid());
		// sleep(1);
	// }
	
	
	//方法2：借助今天学习fork函数，搞个子进程出来，通过子进程执行system
	pid_t id;
	id=fork();
	if(id>0) //父进程
	{
		for(;;)
		{
			printf("main main main，我的ID： %d\n",getpid());
			sleep(1);
		}
	}
	else if(id==0) //子进程
	{
		system("./hello");
	}
}
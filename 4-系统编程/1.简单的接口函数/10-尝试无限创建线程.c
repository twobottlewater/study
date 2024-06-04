#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


#define MAX_THREADS_ATTEMPT 100000 // 尝试创建的最大线程数

#if 0
       #include <pthread.h>

       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

       Compile and link with -pthread.
函数作用：创建一条子线程，执行并发任务（函数）
参数：
        thread：线程的ID号
        attr：线程的属性，一般为NULL    属性：线程的优先级、栈的大小 、自动回收等
        start_routine：线程执行的函数 ，将这个函数的名字传递进来 ----线程例程
        arg：传递给线程例程的参数
返回值：
        成功：返回0
        失败：返回错误号


       #include <pthread.h>

       void pthread_exit(void *retval);

函数作用：主动退出一条子线程
参数：
        retval：线程的退出码 ，退出码是全局变量 / 静态变量

    #include <pthread.h>

    int pthread_join(pthread_t thread, void **retval);
函数作用：接合一条子线程， 也就是阻塞等待子线程的退出，回收子线程的资源，并且如果有需要，可以获取子线程的退出码
参数：
        thread：子线程的ID号 ，你要回收哪个子线程的资源
        retval：子线程的退出码
		
		 Compile and link with -pthread.
        
#endif 



//子线程1的任务
void* timeRoutine(void*arg)
{
    static int th_exit = 0;
    int cnt=5;

    while(cnt--)
    {
        time_t tm = time(NULL);
        printf("timeRoutine:%s %d\n",ctime(&tm),cnt);

        sleep(1);
    }


    //线程的主动退出
    th_exit = 2;
    pthread_exit(&th_exit);
}

int main()
{
	pthread_t threads[MAX_THREADS_ATTEMPT];
	int thread_count = 0;
	int success_count = 0;

	printf("主线程开始尝试创建线程...\n");


	 while (thread_count < MAX_THREADS_ATTEMPT) 
	 { 
        if (pthread_create(&threads[thread_count], NULL, timeRoutine, NULL) == 0) 
		{
            success_count++;
            printf("成功创建线程 %d\n", success_count);
        } 
		else 
		{
            printf("创建线程失败，可能达到系统限制。\n");
            break;
        }
        thread_count++;
    }


	printf("尝试创建了%d个线程。\n", success_count);



    return 0;
}
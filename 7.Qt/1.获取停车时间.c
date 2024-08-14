#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
	//先获取一次系统时间
	time_t t1=time(NULL);
	
	//延时7秒钟
	sleep(7);
	
	//再获取一次系统时间
	time_t t2=time(NULL);
	
	printf("两次时间之间的差值是: %ld\n",t2-t1);
	return 0;
}
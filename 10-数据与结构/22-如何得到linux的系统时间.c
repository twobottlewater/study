#include "myhead.h"

/*
	获取linux系统时间
	time_t time(time_t *tloc)
	   time_t用typedef给长整型取的别名
	   返回值：返回当前系统时间距离1970-1-1凌晨的秒数
	     参数：保存当前系统时间距离1970-1-1凌晨的秒数
    人类习惯阅读字符串格式的时间,需要转换
	   char *ctime(const time_t *timep);
	        返回值：字符串格式的时间
*/

int main()
{
	time_t mytime;
	//死循环，每隔一秒钟获取一次系统时间
	while(1)
	{
		mytime=time(NULL);
		printf("当前系统时间距离1970-1-1凌晨的秒数是:%ld\n",mytime);
		
		//转换成人类习惯的字符串格式时间
		printf("当前系统时间是: %s\n",ctime(&mytime));
		sleep(1); //延时1秒钟
	}
}

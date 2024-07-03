#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//测试用例
#if 0
char buf[2]

buf[0]  ---灯的亮灭
buf[1]  ---第几盏灯   D7  D8  D9  D10

#endif 

int main(void)
{
	//定义与驱动程序相同的数据格式
	char buf[2];
	//1.打开文件
	int fd = open("/dev/led_drv",O_RDWR);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	
	//2.利用与驱动程序相同的接口，来达到调用驱动程序的接口效果
	while(1)
	{

		// buf[0] = 1; //开灯
		// buf[1] = 7;
		// write(fd,buf,sizeof(buf));
		// sleep(1);
		
		// buf[0] = 0; //关灯
		// buf[1] = 7;
		// write(fd,buf,sizeof(buf));
		// sleep(1);

		buf[0] = 1; //开灯
		buf[1] = 8;
		write(fd,buf,sizeof(buf));
		sleep(1);
		
		buf[0] = 0; //关灯
		buf[1] = 8;
		write(fd,buf,sizeof(buf));
		sleep(1);

	}
	
	
	//3.关闭文件
	 close(fd);
	return 0;
}
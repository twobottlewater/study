#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <strings.h>
#include <linux/input.h>
#include "rfid.h"
int open_serial();

int main(void)
{
	int ret, i;
	
	//打开串口文件
	int fd = open_serial();
	
	/*初始化串口*/
	init_tty(fd);
	
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	
	while(1)
	{	
		//发送A命令
		ret = PiccRequest(fd);
		if(ret == -1)  //若是请求超时退出，必须要关闭串口后，重新打开才能再次读取数据
		{
			usleep(500000);
			close(fd);
			
			//打开串口文件
			fd = open_serial();
			/*初始化串口*/
			init_tty(fd);
			timeout.tv_sec = 1;
			timeout.tv_usec = 0;
			continue;
		}	
		
		else//(ret == 0)
		{
			printf("ok!\n");
		}
		//发送B命令 和获取卡号
		ret = PiccAnticoll(fd);
		
		//若获取的cardid为0，或获取id超时，则需重新发送'A'命令
		if(cardid == 0 || ret == -1) continue; 
		else if(ret == 0)
		{
			printf("card ID = %x\n", cardid);  //打印cardid号
			usleep(500000);
			//break;
		}
	}
	close(fd);
	return 0;
}

int open_serial()
{
	int fd;

	fd = open("/dev/ttySAC1", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd < 0)
	{
		printf("Open /dev/ttySAC1 fail!\n");
		return -1;
	}
	return fd;
}



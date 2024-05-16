#include "myhead.h"

/*
	系统IO读取触摸屏坐标值
*/
int main()
{
	int tsfd;
	//定义输入子系统提供的结构体变量来存放坐标
	struct input_event myevent;
	
	//打开触摸屏的驱动
	tsfd=open("/dev/input/event0",O_RDWR);
	if(tsfd==-1)
	{
		perror("打开触摸屏失败了!\n");
		return -1;
	}
	
	while(1) //循环读取坐标
	{
		//读取触摸屏的坐标值
		read(tsfd,&myevent,sizeof(myevent));
		//判断事件类型--》触摸事件
		if(myevent.type==EV_ABS) //是触摸事件
		{
			//进一步判断读取是x坐标，还是y坐标
			if(myevent.code==ABS_X) //是x坐标
				printf("读取的x坐标是: %d\n",myevent.value);
			if(myevent.code==ABS_Y) //是y坐标
				printf("读取的y坐标是: %d\n",myevent.value);	
		}
	}
	
	
	//关闭触摸屏
	close(tsfd);
	return 0;
}
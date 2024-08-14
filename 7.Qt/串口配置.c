void init_tty(int fd)
{    
	//声明设置串口的结构体
	struct termios termios_new;
	
	//先清空该结构体
	bzero( &termios_new, sizeof(termios_new));
	
	//	cfmakeraw()设置终端属性，就是设置termios结构中的各个参数。
	cfmakeraw(&termios_new);
	
	//设置波特率
	//termios_new.c_cflag=(B9600);
	cfsetispeed(&termios_new, B9600);
	cfsetospeed(&termios_new, B9600);
	
	//CLOCAL和CREAD分别用于本地连接和接受使能，因此，首先要通过位掩码的方式激活这两个选项。    
	termios_new.c_cflag |= CLOCAL | CREAD;
	
	//通过掩码设置数据位为8位
	termios_new.c_cflag &= ~CSIZE;
	termios_new.c_cflag |= CS8; 
	
	//设置无奇偶校验
	termios_new.c_cflag &= ~PARENB;
	
	//一位停止位
	termios_new.c_cflag &= ~CSTOPB;
	//tcflush(fd,TCIFLUSH);
	
	// 可设置接收字符和等待时间，无特殊要求可以将其设置为0
	termios_new.c_cc[VTIME] = 2;
	termios_new.c_cc[VMIN] = 1;
	
	// 用于清空输入/输出缓冲区
	tcflush (fd, TCIFLUSH);
	
	//完成配置后，可以使用以下函数激活串口设置
	tcsetattr(fd,TCSANOW,&termios_new);

}
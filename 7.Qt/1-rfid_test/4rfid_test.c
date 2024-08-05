/************************************************
*  * note: Smart Home RFID test program
*  * date: 2012-07-14
************************************************/
#include "rfid.h"



/* ���ô��ڲ���:9600���� */
void init_tty(int fd)
{    
	//�������ô��ڵĽṹ��
	struct termios termios_new;
	
	//����ոýṹ��
	bzero( &termios_new, sizeof(termios_new));
	
	//	cfmakeraw()�����ն����ԣ���������termios�ṹ�еĸ���������
	cfmakeraw(&termios_new);
	
	//���ò�����
	//termios_new.c_cflag=(B9600);
	cfsetispeed(&termios_new, B9600);
	cfsetospeed(&termios_new, B9600);
	
	//CLOCAL��CREAD�ֱ����ڱ������Ӻͽ���ʹ�ܣ���ˣ�����Ҫͨ��λ����ķ�ʽ����������ѡ�    
	termios_new.c_cflag |= CLOCAL | CREAD;
	
	//ͨ��������������λΪ8λ
	termios_new.c_cflag &= ~CSIZE;
	termios_new.c_cflag |= CS8; 
	
	//��������żУ��
	termios_new.c_cflag &= ~PARENB;
	
	//һλֹͣλ
	termios_new.c_cflag &= ~CSTOPB;
	//tcflush(fd,TCIFLUSH);
	
	// �����ý����ַ��͵ȴ�ʱ�䣬������Ҫ����Խ�������Ϊ0
	termios_new.c_cc[VTIME] = 10;
	termios_new.c_cc[VMIN] = 1;
	
	// �����������/���������
	tcflush (fd, TCIFLUSH);
	
	//������ú󣬿���ʹ�����º������������
	tcsetattr(fd,TCSANOW,&termios_new);

}


/*����У���*/
unsigned char CalBCC(unsigned char *buf, int n)
{
	int i;
	unsigned char bcc=0;
	for(i = 0; i < n; i++)
	{
		bcc ^= *(buf+i);
	}
	return (~bcc);
}

//����A����
int PiccRequest(int fd)
{
	unsigned char WBuf[128], RBuf[128];
	int  ret, i,len=0;
	fd_set rdfd;
	
	memset(WBuf, 0, 128);  //�������
	memset(RBuf,0,128);
	
	
	WBuf[0] = 0x07;	//֡��= 7 Byte
	WBuf[1] = 0x02;	//����= 0 , ��������
	WBuf[2] = 0x41;	//����= 'A'
	WBuf[3] = 0x01;	//��Ϣ����
	WBuf[4] = 0x52;	//����ģʽ:  ALL=0x52
	WBuf[5] = CalBCC(WBuf, WBuf[0]-2);		//У���
	WBuf[6] = 0x03; 	//������־
	
	while(1)
	{
		FD_ZERO(&rdfd);
		FD_SET(fd,&rdfd);
		tcflush (fd, TCIFLUSH);  
		
		write(fd, WBuf, 7);
		
	
		ret = select(fd + 1,&rdfd, NULL,NULL,&timeout);  //����ļ��������ı仯
		switch(ret)
		{
			case -1:
				perror("select error\n");
				break;
			case  0:
				len++;   //3������ʱ���˳��ú���
				if(len == 3)
				{
					len=0;
					return -1;
				}
				
				//printf("Request timed out.\n");
				break;
			default:
				usleep(10000);
				ret = read(fd, RBuf, 8);
				
				if(ret < 0)
				{
					printf("len = %d, %m\n", ret, errno);
					break;
				}
				
				//printf("RBuf[2]:%x\n", RBuf[2]);
				if(RBuf[2] == 0x00)	 	//Ӧ��֡״̬����Ϊ0 ������ɹ�
				{
					return 0;
				}
				break;
		}
		
		usleep(100000);
		
	}
	
	return -1;
}


/*����ײ����ȡ��Χ�����ID*/
int PiccAnticoll(int fd)
{
	//printf("fd = %d\n", fd);

	unsigned char WBuf[128], RBuf[128];
	int ret=1, i,len=0;
	fd_set rdfd;
	
	memset(WBuf, 0, 128);
	memset(RBuf,1,128);
	
	WBuf[0] = 0x08;	//֡��= 8 Byte
	WBuf[1] = 0x02;	//����= 0 , ��������= 0x01
	WBuf[2] = 0x42;	//����= 'B'
	WBuf[3] = 0x02;	//��Ϣ����= 2
	WBuf[4] = 0x93;	//����ײ0x93
	WBuf[5] = 0x00;	//λ����0
	WBuf[6] = CalBCC(WBuf, WBuf[0]-2);		//У���
	WBuf[7] = 0x03; 	//������־
	
	 
	while(1)
	{
		
		tcflush (fd, TCIFLUSH);
		FD_ZERO(&rdfd);
		FD_SET(fd,&rdfd);
		
		write(fd, WBuf, 8);
		
		ret = select(fd + 1,&rdfd, NULL,NULL,&timeout);
		switch(ret)
		{
			case -1:
				perror("select error\n");
				break;
			case  0:
				len++;
				if(len == 10)
				{
					len=0;
					return -1;
				}
				perror("Timeout:");
				break;
				
			default:
				usleep(10000);
				ret = read(fd, RBuf, 10);
				if (ret < 0)
				{
					printf("ret = %d\n", ret);
					break;
				}
				if (RBuf[2] == 0x00) //Ӧ��֡״̬����Ϊ0 ���ȡID �ɹ�
				{
					cardid = (RBuf[4]<<24) | (RBuf[5]<<16) | (RBuf[6]<<8) | RBuf[7];
					
					return 0;
				}
		}

	}
	
	return -1;
}

#include "myhead.h"

/*
	1.txt��ǰ������hello
*/
int main()
{
	int fd;
	char buf[20]={0};
	fd=open("1.txt",O_RDWR);
	
	//��ʼλ������/����ƫ��10���ֽ�
	//lseek(fd,10,SEEK_SET); //��ʼλ������ƫ�ƣ��м����ո�
	lseek(fd,-10,SEEK_SET); //��ʼλ����ǰƫ�ƣ�û���κ�����
	//����д��
	//write(fd,"world",5);
	//���Զ�ȡ
	read(fd,buf,5);
	printf("buf is: %s\n",buf);
		
	//�ر�
	close(fd);
	return 0;
}
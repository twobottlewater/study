#include "myhead.h"

/*
	1.txt��ǰ������hello
*/
int main()
{
	int fd;
	char buf[20]={0};
	fd=open("1.txt",O_RDWR);
	
	//��ʼλ������/����ƫ��100���ֽ�
	//lseek(fd,100,SEEK_SET); //��ʼλ������ƫ�ƣ��м����ո�
	//lseek(fd,-100,SEEK_SET);  //��ʼλ���޷���ǰƫ��
	
	//�ȶ�ȡ5���ֽ�
	read(fd,buf,5);
	printf("buf is: %s\n",buf);
	
	//��ǰλ������/����ƫ�Ƹ��ֽ�
	lseek(fd,-2,SEEK_CUR); //��ǰλ����ǰƫ��
	
	//�ȶ�ȡ3���ֽ�
	bzero(buf,20);
	read(fd,buf,3); 
	printf("buf is: %s\n",buf);
	
	//�ر�
	close(fd);
	return 0;
}
#include "myhead.h"

/*
	1.txt��ǰ������helloworldchinahehexixi
	�ܽ᣺
	    ��һ��ͷ�Բ�����--����ͼ����
              �ʼopen��(����ʹ��O_APPEND)�����ӵ�һ���ַ�ǰ�濪ʼ��  
        �ڶ���read����write��궼��䶯
        ������lseek�����￪ʼ�ƶ����(�����۾����������������͵ڶ�������)	
        ���ģ�read/write���ӹ�����һ��λ�ÿ�ʼ		
*/
int main()
{
	int fd;
	char buf[20]={0};
	fd=open("1.txt",O_RDWR);
	
	//��ʼλ������ƫ��10���ֽ�
	lseek(fd,3,SEEK_SET); //û�и����lseek���һ��������ʲô
	//���Զ�ȡ
	read(fd,buf,2);
	printf("buf is: %s\n",buf); //lo
	
	//��ǰλ������ƫ��3���ֽ�
	lseek(fd,3,SEEK_CUR);  //û�и����lseek���һ��������ʲô
	write(fd,"gec",3);
	
	//��ǰλ����ǰƫ��5���ֽ�
	bzero(buf,20);
	lseek(fd,5,SEEK_CUR);  //û�и����lseek���һ��������ʲô
	read(fd,buf,4);
	printf("buf is: %s\n",buf); //ehex
	
	//��ʼλ������ƫ��5���ֽ�
	bzero(buf,20);
	lseek(fd,5,SEEK_SET); //û�и����lseek���һ��������ʲô
	//���Զ�ȡ
	read(fd,buf,5);
	printf("buf is: %s\n",buf); //worge	
	//�ر�
	close(fd);
	return 0;
}
#include "myhead.h"


/*
fread �� fwrite �������ļ�
*/
	
int main(int argc,char **argv)
{
	FILE *srcfile;
	FILE *destfile;
	ssize_t ret;
	//�������������
	char buf[1024*1024];

	srcfile=fopen(argv[1],"r+");//�ɶ���д�ķ�ʽ
	if(srcfile==NULL)
	{
		perror("��Դ�ļ�ʧ����!\n");
		return -1;
	}
	
	destfile=fopen(argv[2],"w+");
	if(destfile==NULL)
	{
		perror("打开失败\n");
		return -1;
	}
	
	while(1)
	{
		//��ȡ
		ret=fread(buf,1,1024*1024,srcfile);
		//д��ȥ
		
		if(ret==0)
		break;
	
		fwrite(buf,1,ret,destfile);
		if(feof(srcfile))
		break;
	}
	fclose(srcfile);
	fclose(destfile);
	return 0;
}
#include "myhead.h"


/*
fprintf���԰Ѳ�ͬ����������д�뵽�ļ���
*/
	
int main(int argc,char **argv)
{
	FILE *srcfile;
	int year=2000;
	double score=85.5;
	char buf[50]="�����ĳ��������:";
	//���ļ�
	srcfile=fopen(argv[1],"r+");//�ɶ���д�ķ�ʽ
	if(srcfile==NULL)
	{
		perror("��Դ�ļ�ʧ����!\n");
		return -1;
	}
		
	fprintf(srcfile,"%s%d,�����˶��ٷ�:%lf��",buf,year,score);

	
	
	fclose(srcfile);
	
	return 0;
}
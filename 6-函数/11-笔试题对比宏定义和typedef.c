#include <stdio.h>
#define INTP int *  //�궨��--�ȼ���int *
typedef int * intp; //��int *ȡ�˱�������intp
/*
	intp p,*q; //�ܶ�ͬѧ������д���Ի�
	//��ʦ֧��
	intp p;
	intp *q;

*/

int main()
{
	int a=99;
	int b=78;
	intp p,*q;  
	INTP p1,*q1;  //int *p1,*q1;
	
	//֤��p��һ��ָ��
	p=&a;
	
	//֤��q�Ƕ���ָ��
	q=&p;
	
	//֤��p1��һ��ָ��
	p1=&a;
	//֤��q1��һ��ָ��
	q1=&b;
	
}
#include "myhead.h"

int main()
{ 
		/*int a=9;
		int b=8;
		if(a==b)
		{
		printf("值是is：%d",(a==b));
		}*/
		
	
		
		
		char buf[20]={0};
		char otherbuf[32]="ww";
		char (*a)[32];
		a=&otherbuf;
		//printf("bufmei is : %d\n",buf[0]);
		//printf("buf+4  jia is : %d\n",buf+4);

		printf("buf  指针 is： %p\n",buf);
		printf("buf+1  指针 is： %p\n",buf+1);
		printf("otherbuf  指针 is： %p\n",otherbuf);
		printf("otherbuf+1  指针 is： %p\n",otherbuf+1);
		printf("a 指针 is： %p\n",a);
		printf("a+1	指针 is： %p\n",a+1);
		return 0;
	
		/*double a=89;  
		double *p=&a;    
		printf("p is: %p\n",p);   
		printf("p-1 is: %p\n",p-1);*/
	
}
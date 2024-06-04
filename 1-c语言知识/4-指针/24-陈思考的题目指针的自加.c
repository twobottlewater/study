#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

int main()
{
   
    int buf[8]={45,96,12,98,23,56,58,687};
    int *p=&buf[2];
    printf("1 %d\n",p++);
    printf("2 %d\n",*p);
    printf("3 %d\n",(*p)++);
    printf("4 %d\n",*p);
    printf("5 %d\n",*++p);
    printf("6 %d\n",*p);
    printf("7 %d\n",++*p);

}


/*
    第一行，printf 函数输出 p 的地址，即 随机一个地址数。注意哈,加之前的地址是在12上面 加了之后再98了
    第二行，printf 函数输出 *p 的值，即 98。
    第三行，*p 自增 1，因此 *p 的值变为 99,但是立刻输出是*p加之前的值,所以还是输出98。
    第四行，printf 函数输出 *p 的值，即 99。
    第五行，*p 自增 1，因此 *p 的值变为99这个数的下面一个数的地址 *p里面的东西就是99下面一个的23了 。
    第六行，printf 函数输出 *p 的值，即 23。
    第七行，*p 取出来再自增 1，因此 *p 的值变为24。
*/








/*
	int a=78;
	char b='@';
	double c=89.6;
	float d=56.7;
	
	int *p1=&a;
	char *p2=&b;
	double *p3=&c;
	float *p4=&d;
	
	printf("p1指向的地址是: %p\n",p1);
	printf("p2指向的地址是: %p\n",p2);
	printf("p3指向的地址是: %p\n",p3);
	printf("p4指向的地址是: %p\n",p4);
	
	//指针做了加法运算
	printf("p1+1指向的地址是: %p\n",p1+1); 
	printf("p2+1指向的地址是: %p\n",p2+1); 
	printf("p3+1指向的地址是: %p\n",p3+1); 
	printf("p4+1指向的地址是: %p\n",p4+1); 
*/
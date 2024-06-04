#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void test(void)   
{
	char *str = (char *)malloc(100);
	char *p=str;
	strcpy(str, "hello");
	printf("堆空间的首地址是: %p\n",str);
	/*
	   肤浅的理解：
		理解1：free把指针设置为NULL
		理解2：free把指针刚才指向的堆空间数据清空
		理解3：free之后，指针指向的堆空间就不能使用，非法，用了段错误
	   正确的理解:
	    free只是把指针指向堆空间的所有权转让给操作系统，接下来操作系统如何来处理这块内存区域，有很多种可能性(不是由程序员可以决定的)
		      可能性1：free把堆空间的所有权转让给操作系统，操作系统立马给其他程序使用了，此时该指针不能再使用刚才的内存区域
			  可能性2：free把堆空间的所有权转让给操作系统，操作系统暂时还没有把这块区域给其他程序，因此该 指针依旧可以访问刚才的内存区域 
	*/
	free(str); //释放堆空间，你真的理解什么叫做释放堆空间
	//strcpy(p,"yueqian"); //很危险，可能成功，可能失败
	//printf("p指向的内存中存放的是: %s\n",p);
	
	//free完毕之后，我还可以继续访问str里面的内容吗？？ free完毕之后，我还可以继续访问str里面的内容吗？？
	//free之后，str指向哪里也是不确定
	printf("free完毕之后，我还可以继续访问str里面的内容吗？？ %s\n",str);

	if(str != NULL)
	{
		printf("free完毕str指向哪里呢: %p 如果还是指向原理的堆空间，hello还不在不呢,内容: %s\n",str,str);
		strcpy(str, "world");  //50%的成功率
		printf("%s\n", str);
	}
}

int main()
{
	test();
}
#include <stdio.h>
 
 
 /*
		char类型的二维数组就是实际开发来存放多个字符串的
		写法1 ：
		例如 char a[2][10]={"/1.txt","2.mp3"};
 */
int main()
{
	
	
	int i,j;
	
	/* 写法2
	char a[2][10]={"/1.txt"}; 
	*/ 
	
	
	//写法3  省略下标
	char a[][3]={'h','e','l','l','o'};
	printf("sizeof(a)is:%d\n",sizeof(a));
	//答案是6.太简单了这题，一个列下标就出卖了他，5个字符是用了2行一行3个元素一共6个元素，所以用了6个字节 easy！
		
		
	/* 
	//当字符打一个个打
	for(i=0; i<2; i++) //行
	{
		for(j=0; j<10; j++) //列
			printf("a[%d][%d] is: %c  ASCII码值：%d\n",i,j,a[i][j],a[i][j]);
	} 
	*/
	
	//当字符串打
	for(i=0; i<2; i++) //行
	{
	printf("存放的字符串是%s\n",a[i]);
	}
	
	return 0;
}
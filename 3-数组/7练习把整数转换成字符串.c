#include <stdio.h>
#include <string.h>
int main()
{
	int num;
	char buf[5]={0};//"/0"的ASCII的值就是0,完美!
    int temp;
	int i=0;
    int j=0;
    
	
	printf("请输入整数\n");
	scanf("%d",&num);
	
	//求出各个位，转换位字符存放到char类型的数组里
	while(num!=0)
	{
		temp=num%10;//中间变量保存住个位
		//把个位转换成字符
		//加字符'0'的ascii码就可以转字符
		buf[i]=temp+'0';
		i++;
		num/=10;
		
	}
	//数组倒序实践
	for(i=0,j=strlen(buf)-1;i<strlen(buf)/2;i++,j--)
	{
		temp=buf[i];
		buf[i]=buf[j];
		buf[j]=temp;
		
	}
	//打印结果 
	printf("转换结果是:%s\n",buf);
	
	
}
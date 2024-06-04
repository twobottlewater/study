#include <stdio.h>

int main()
{
	char ch='A';
	int i,j,k;
	int n; //图案总的行数
	printf("请输入图案总的行数!\n");
	scanf("%d",&n);
	//打印三角形
	for(i=1; i<=n; i++) //i表示行号
	{
		//打印空格
		for(j=0; j<n-i; j++)
			printf(" ");
		//打印字母--》小学生观察规律
		/*
			每一行的字母规律如下：
			     第i行，前面i个字母分别是   A  A+1 A+2.......A+i-1
				 第i行，后面i-1个字母分别是 A+i-2  A+i-3.......A
		*/
		//打印前面i个字母
		for(j=0; j<i; j++)
			printf("%c",ch+j);
		//以第4行为例
		//打印后面i-1个字母
		for(k=1; k<=i-1; k++)		
			printf("%c",ch+j-1-k);
		
		//打印回车换行
		printf("\n");
	}
}
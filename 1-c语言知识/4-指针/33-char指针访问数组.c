#include <stdio.h>

/*
	指针如果要跟数组写法一模一样，前提条件是该指针类型必须跟数组名代表的指针类型一致
*/
int main()
{
	int i,j;
	char a[3][10]={"hello","world","gec"};


    
    /* 写法1
    char *p=&a[0][0];
    for ( i = 0; i< 15; i++)
    {
        printf("*(p+%d) is %c\n",i,*(p+i));
    }
    */
    

	//写法2：受到第19--24行代码的启发，定义一个指针跟数组名a类型相同，不就解决问题吗
	char (*q)[10]=a;  //q跟a类型一致，因此可以等价替换
	for(i=0; i<3; i++)
	{
		for(j=0; j<10; j++)
			printf("模仿数组名的写法q[%d][%d] is: %c\n",i,j,q[i][j]);
	}

}
#include "myhead.h"
/*
从小到大排序
思想：每轮循环找到最小的，然后排到前面
        第一轮循环中找到目前最小的数，把下标记录下来
      然后用最小数的下标跟下标0比较，不想等就交换这两个数的位置(即把最小的数放到最前面(下标为0的位置))
	    第二轮循环中找到目前次小的数，把下标记录下来，然后跟下标1比较，不想等就交换这两个数的位置
*/

void selectsort(int buf[],int n)
{
	int i,j,min,temp;
	for(i=0; i<n-1; i++) //循环多少轮
	{
		min=i; //假设下标i的是最小的数
		//寻找目前最小的那个数
		for(j=i+1; j<n; j++)
		{
			if(buf[j]<buf[min])
				min=j; 
		}
		//上面循环结束的时候，min保存了目前数组最小的那个数所在的下标位置
		if(min!=i)
		{
			temp=buf[min];
			buf[min]=buf[i];
			buf[i]=temp;
		}
	}
}

int main()
{
	int i;
	int buf[6]={10,7,98,2,963,9};
	selectsort(buf,6);
	
	for(i=0; i<6; i++)
		printf("数组中元素: %d\n",buf[i]);
}
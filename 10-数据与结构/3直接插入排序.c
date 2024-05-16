#include "myhead.h"
/*
从小到大排序
思想：每轮循环找到最小的，然后排到前面
        第一轮循环中找到目前最小的数，把下标记录下来
      然后用最小数的下标跟下标0比较，不想等就交换这两个数的位置(即把最小的数放到最前面(下标为0的位置))
	    第二轮循环中找到目前次小的数，把下标记录下来，然后跟下标1比较，不想等就交换这两个数的位置
*/

void insertsort(int buf[],int n)
{
	int i,j,temp;
	for(i=1; i<n; i++)  
	{
		if(buf[i]<buf[i-1])
		{
			//把i位置的数据备份
			temp=buf[i];
			for(j=i-1; buf[j]>temp && j>=0; j--) //把前面排好序的挪动，找到temp存放的位置
			buf[j+1]=buf[j];

		
			buf[j+1]=temp;
		}
	}


}


int main()
{
	int i;
	int buf[6]={10,7,98,2,963,9};
	insertsort(buf,6);
	
	for(i=0; i<6; i++)
		printf("数组中元素: %d\n",buf[i]);
	return 0;
}
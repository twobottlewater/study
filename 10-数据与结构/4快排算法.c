 #include "myhead.h"

void sort(int a[], int left, int right)
{
	int tem;
	int j,k;
	int buf;
	if(left >  right) //0    9
       return; 
	tem = a[left];//初始化基准数a[0]==3
	j = left;
	k = right;
	
	while(j != k) //        2 1 3 5  j==1     k==1 
	{
		while(a[k] >= tem && j != k)//从右开始寻找比基准数小的数
		k--;
		while(a[j] <= tem && j != k)//从左开始找比基准数大
		j++;
		if(j != k)             //交换位置
		{
			buf = a[k];
			a[k] = a[j];
			a[j] = buf;
		}
// 只要左边的下标j和右边的下标k重叠了，就退出上面的循环了，
	a[left] = a[j];//将基准数放在合适的位置  1 1 3 5  
	a[j] = tem;  //此时的j是个分界线          1 2 3 5
	
	sort(a,left,j - 1); //继续进行左区域的排序 
	sort(a,j + 1,right);//继续进行右区域的排序
	
	return;
	
}
}

int main()
{
	int i;
	int twobuf[]={9,5,6,8,4,7,1,3,2,10};
	sort(twobuf,0,9);
	
	for(i=0; i<10; i++)
		printf("数组中元素: %d\n",twobuf[i]);
	
	return 0;
}
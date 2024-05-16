#include "myhead.h"

//定义结构体来表示顺序表
/*
	顺序表总结成公式：
	    struct 顺序表名字
		{
			数组; //存放真实数据
			int last; //存放最后一个有效元素下标
		}
*/
#define N 10
struct seqlist
{
	int buf[N]; //存放真实数据
	int last; //存放最后一个有效元素下标
};

//顺序表的初始化
struct seqlist *list_init()
{
	//想法1：局部变量(作用域只能在该函数中使用)，栈空间
	//struct seqlist list;
	//想法2：堆空间，不会立马释放，把指针作为返回值给其它函数使用
	struct seqlist *list=malloc(sizeof(struct seqlist));
	list->last=-1;
	return list;
}

//尾插数据
/*
	参数：n表示你要尾插到顺序表中的某个数
	      list表示你即将要插入的那个顺序表
*/
int list_add_tail(int n,struct seqlist *list)
{
	//判断顺序表(数组越界了)是否满了
	if(list->last>=N-1)
	{
		printf("顺序表满了!\n");
		return -1;
	}
	//更新last
	list->last++;
	//把新的数据存放到last的位置
	list->buf[list->last]=n;
	return 0;
}

//删除数据
/*
	参数：n表示你要删除的数据
	      list表示你要操作的那个顺序表
	情况1：n不存在？
	情况2：n有多个？全部删除
	情况3：顺序表空了，不能删除
*/
int list_delete(int n,struct seqlist *list)
{
	int i,j;
	//定义标志位记录n是否存在
	int flag=0;
	
	//判断顺序表是否为空
	if(list->last<0)
	{
		printf("对不起，顺序表空了，无法删除!\n");
		return -1;
	}
	//找到要删除的数据
	for(i=0; i<=list->last; i++)
	{
		if(list->buf[i]==n) //找到要删除的数据
		{
			//后面的往前挪动
			for(j=i; j<list->last; j++)
				list->buf[j]=list->buf[j+1];
			
			//防止漏掉连续重复的数据
			i--;
			//更新last
			list->last--;
			
			//更新flag
			flag=1;
		}
	}
	
	//判断flag的值
	if(flag==0)
	{
		printf("%d是不存在的，无法删除!\n",n);
		return -1;
	}
	return 0;
}

//修改数据
/*
	参数：oldn表示顺序表中旧的数据
	      newn表示替换oldn的新数据
	      list表示你要操作的那个顺序表
	情况1：oldn不存在？
	情况2：oldn有多个？全部修改
*/
int list_update(int oldn,int newn,struct seqlist *list)
{
	int i;
	//定义标志位记录oldn是否存在
	int flag=0;
	//找到要修改的数据
	for(i=0; i<=list->last; i++)
	{
		if(list->buf[i]==oldn) //找到要修改的数据
		{
			list->buf[i]=newn;
			flag=1;
		}
	}
	
	if(flag==0)
	{
		printf("%d数据是不存在的!\n",oldn);
		return -1;
	}
	return 0;
}

//查询打印数据
int list_show(struct seqlist *list)
{
	int i;
	for(i=0; i<=list->last; i++)
		printf("当前顺序表中存放的有效数据是: %d\n",list->buf[i]);
	return 0;
}
int main()
{
	//顺序表的初始化
	struct seqlist *mylist=list_init();
	
	//往顺序表中尾插数据
	list_add_tail(5,mylist);
	list_add_tail(8,mylist);
	list_add_tail(8,mylist);
	list_add_tail(8,mylist);
	list_add_tail(96,mylist);
	list_add_tail(8,mylist);
	list_add_tail(8,mylist);
	list_add_tail(8,mylist);
	
	//验证数据是否存放成功
	list_show(mylist);
	
	//删除数据
	list_delete(8,mylist);
	//list_delete(5,mylist);
	//list_delete(96,mylist);
	//list_delete(100,mylist);
	//printf("===================删除之后===================\n");
	//list_show(mylist);
	
	//修改数据
	//list_update(8,666,mylist);
	printf("===================修改之后===================\n");
	list_show(mylist);
}
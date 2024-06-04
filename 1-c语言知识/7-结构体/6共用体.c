#include <stdio.h>
//定义联合体
union sex //表示性别
{
	char man;    //是男的，man  1 woman 0
	char woman;  //是女的，man  0 woman 1
};

//拿个结构体对比一下
struct mysex //表示性别
{
	char man;    
	char woman;  
};
int main()
{
	//定义联合体变量
	struct mysex s2;
	union sex s1;
	s1.man=1;
	s1.woman=0;
	
	//打印一下结果
	printf("s1.man is: %d\n",s1.man);
	printf("s1.woman is: %d\n",s1.woman);
	
	//打印联合体的大小
	printf("sizeof(union sex) is:%ld\n",sizeof(union sex));
	printf("sizeof(struct mysex) is:%ld\n",sizeof(struct mysex));
	
	//证明联合体成员公用同一块内存区域
	printf("联合体man的地址：%p\n",&(s1.man));
	printf("联合体woman的地址：%p\n",&(s1.woman));
	printf("结构体man的地址：%p\n",&(s2.man));
	printf("结构体woman的地址：%p\n",&(s2.woman));
}
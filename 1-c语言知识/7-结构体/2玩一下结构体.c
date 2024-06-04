#include <stdio.h>
#include<stdbool.h>
#include<string.h>
#include<strings.h>
//定义一个学生的结构体
struct student
{
	char name[10];//结构体里面的一个成员
	int age;//结构体里面的一个成员
	float score;//结构体里面的一个成员
	char address[100];//结构体里面的一个成员
};

int main()
{
	//定义结构体变量-->>跟定义int类型变量写法一样
	//int a;
	//写法一:
	//我定义了一个struct student的类型变量,变量名叫stu1
	
	struct student stu1={"张三",18,85.5,"天河珠江新城"};
	
	//写法二:没有初始化
	struct student stu2;
	//结构体里面的成员,必须使用结构体变量来调用,不能单独使用
	strcpy(stu2.name,"李华");
	stu2.age=28;
	stu2.score=99;
	strcpy(stu2.address,"江门市五邑大学");
  //打印测试
	printf("姓名:%s\n",stu2.name);
	printf("年龄:%d\n",stu2.age);
    printf("成绩:%f\n",stu2.score);
	printf("住址:%s\n",stu2.address);
  
  return 0;
}
#include <stdio.h>

#include<string.h>

struct book
{
	char bookname[20];
	float bookprice;
};
struct student
{
	struct book b1;
	
	char name[10];
};

int main()
{
	struct student stu;
	strcpy(stu.b1.bookname,"<活着>");
	stu.b1.bookprice=78.9;
	strcpy(stu.name,"李四");
}

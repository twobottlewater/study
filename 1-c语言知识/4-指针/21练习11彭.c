#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main() {
  int i,j;
  int flag1=0,flag2=0,flag3=0;
  char buf[5][10];

  for(i=0;i<5;i++)
  {printf("请输入第%d个用户名字\n",i+1);scanf("%s",buf[i]);}
	  
  
  
  //判断字符串是否符合要求
  for(i=0;i<5;i++)
  {
	  if(strlen(buf[i])<=8)
	  {
		  //把标志位清零
		  flag1=0; flag2=0; flag3=0;
		  
		  //进一步判断是否包含了大写,小写,数字字符
		  for(j=0;j<strlen(buf[i]);j++)
		  {
			  if(buf[i][j]>='a' && buf[i][j]<='z')
			  flag1=1;
			  if(buf[i][j]>='A' && buf[i][j]<='Z')
			  flag2=1;
			  if(buf[i][j]>='0' && buf[i][j]<='9')
			  flag3=1;
		  }
		  //判断标志位的值
		if(flag1==1&&flag2==1&&flag3==1)
		  printf("用户名%d符合要求\n",i+1);
		if(flag1==0)
		  printf("用户名%d没有小写字母\n",i+1);
		if(flag2==0)
		  printf("用户名%d没有大写字母\n",i+1);
		if(flag2==0)
		  printf("用户名%d没有数字\n",i+1);
		  
	  }
	  else{
		  printf("用户%d名字过长",i+1);
	  }
  }
  return 0;
}

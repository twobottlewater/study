#include "myhead.h"

/*
	彭老师想要知道百度服务器的ip
	只知道百度的网址：www.baidu.com
*/
int main()
{
	struct hostent *p=gethostbyname("www.baidu.com");
	
	//打印网址对应的信息
	printf("百度对应的官方名字: %s\n",p->h_name);
	printf("百度对应的别名: %s\n",*(p->h_aliases));
	
	//重点注意：打印ip地址 p->h_addr_list存放的是大端序的ip
	struct in_addr *q=(struct in_addr *)(*(p->h_addr_list));
	printf("百度服务器的ip地址: %s\n",inet_ntoa(*q));
	
	q=(struct in_addr *)(*(p->h_addr_list+1));
	printf("百度服务器的ip地址: %s\n",inet_ntoa(*q));

}
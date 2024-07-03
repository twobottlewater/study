#include "myhead.h"

/*
	ftok产生键值
*/


int main()
{
	key_t mykey=ftok("/home/gec",4);
	printf("生成的键值是: %d\n",mykey);
	
	mykey=ftok("/home/gec",4);
	printf("生成的键值是: %d\n",mykey);
	
	mykey=ftok("/home/gec",5);
	printf("生成的键值是: %d\n",mykey);
	
	mykey=ftok("/home",4);
	printf("生成的键值是: %d\n",mykey);

	return 0;
}
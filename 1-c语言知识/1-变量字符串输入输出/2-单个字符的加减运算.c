#include <stdio.h>

int main()
{
	int x='c';
	
	printf("%c\n",'a'+(x-'a'+1));
	return 0;
}
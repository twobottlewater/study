#include <stdio.h> 
#include <fcntl.h> 

int main(void)
{
    int n = 0;
    while(1)
    {
        int fd = open("a.txt", O_RDWR);

        if(fd > 0)
            n++;

        else
        {
            perror("open()失败");
            break;
        }
    }
    printf("n:%d\n", n);
}
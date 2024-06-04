#include <stdio.h>
#include <time.h>

int main(int argc,char*argv[])
{
    printf("mtime id:%d\n",getpid());
    if(argc>1)
    {
         printf("%s\n",argv[1]);
    }
   
    int n=10;

    while(n--)
    {
        time_t tm = time(NULL);
        struct tm *lTime = localtime(&tm);
        printf("date:%d:%d:%d\n",
                        (1900+lTime->tm_year),
                        (1+lTime->tm_mon),
                        lTime->tm_mday);

        printf("time:%d:%d:%d\n",
                        lTime->tm_hour,
                        lTime->tm_min,
                        lTime->tm_sec);
        sleep(1);
    }

}
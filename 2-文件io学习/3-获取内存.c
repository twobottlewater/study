#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>

int main(int argc,char **argv)
{
    struct sysinfo s_info;
    char info_buff[100];
    do
    {
        if(sysinfo(&s_info)==0)
        {
            sprintf(info_buff,"totalram: %.ld bytes",s_info.totalram);
            printf("%s\n",info_buff);

            sprintf(info_buff,"freeram: %.ld bytes",s_info.freeram);
            printf("%s\n",info_buff);

            sprintf(info_buff,"totalswap: %.ld bytes",s_info.totalswap);
            printf("%s\n",info_buff);

            sprintf(info_buff,"freeswap: %.ld bytes",s_info.freeswap);
            printf("%s\n",info_buff);

            sprintf(info_buff,"uptime: %.ld minutes",s_info.uptime/60);
            printf("%s\n",info_buff);

            printf("\n\n");
        }
        sleep(1);
    } while(0);
    return 0;
}
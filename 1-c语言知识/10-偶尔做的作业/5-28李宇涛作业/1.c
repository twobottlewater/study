#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "/home/xlx/桌面/fifo"
#define FIFO_NAME_TWO "/home/xlx/桌面/fifo2"
int main(int argc,char *argv[])
{
    if(access(FIFO_NAME,F_OK) == -1)
    {
        int ret = mkfifo(FIFO_NAME,0666);
        if(ret == -1)
        {
            perror("mkfifo");
            exit(1);
        }
    }
    if(access(FIFO_NAME_TWO,F_OK) == -1)
    {
        int ret = mkfifo(FIFO_NAME_TWO,0666);
        if(ret == -1)
        {
            perror("mkfifo");
            exit(1);
        }
    }

    char buf[1024];
    bzero(buf,sizeof(buf));
    
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork");
        exit(1);
    }
    if(pid == 0)
    {
        int fd = open(FIFO_NAME,O_RDONLY);
        while(1)
        {
            int ret = read(fd,buf,sizeof(buf));
            if(ret == -1)
            {
                perror("read");
                exit(1);
            }
            if (ret > 0)
            {
            printf("read from fifo:%s\n",buf);
            }
        }
        close(fd);
    }
    if(pid > 0)
    {
        int fd = open(FIFO_NAME_TWO,O_WRONLY);
        while(1)
        {
            printf("please input a string:\n");
            scanf("%s",buf);
            int ret = write(fd,buf,strlen(buf));
            if(ret == -1)
            {
                perror("write");
                exit(1);
            }
        }
        close(fd);
    }

}
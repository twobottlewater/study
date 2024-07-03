#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <cJSON.h>
#include "touch.h"
#include "lcd.h"
#include "bmp.h"
#include "log.h"
#include "dir.h"
#include "mfont.h"

#define SERVER_IP "192.168.1.48"
#define SERVER_PORT 13000

void *wendu_thread(void *arg)
{
    printf("UDP服务器 IP:%s Port:%d\n", SERVER_IP, SERVER_PORT);

    int socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd == -1)
    {
        perror("socket");
        return -1;
    }

    // 设置端口号复用--重复利用
    int opt = 1;
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVER_PORT);
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 2 绑定
    int ret = bind(socketfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (ret == -1)
    {
        perror("bind error");
        return -1;
    }
    // 3 接收数据
    while (1)
    {
        char buf[1024] = {0};

        struct sockaddr_in addr;
        int addrlen = sizeof(addr);

        int ret = recvfrom(socketfd, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &addrlen);
       
        printf("buf =%s\n", buf);

      
     }

    close(socketfd);
}

int wendu()
{  
      
       
    pthread_t tid;
    pthread_create(&tid, NULL, wendu_thread, NULL);
    printf("线程创建成功\n");

    bmp_show("26.bmp", 0, 0);
   
    while (1)
    {
        int x, y;
        touch_wait(&x, &y);
        // 结束
        if (x < 50 && y < 50)
        {
            printf("结束\n");

            bmp_show("1.bmp", 0, 0);
            main();
        }
    }
}
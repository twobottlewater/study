#include<stdio.h>
#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
 #include <unistd.h>


#define SERVER_IP "192.168.1.160"
#define SERVER_PORT 12000


 int main()
 {
    //1.创建套接字
    int socketfd = socket(AF_INET,SOCK_DGRAM,0);
    if(socketfd == -1)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(SERVER_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(SERVER_IP);


    //2 发送数据
    while (1)
    {
       int value;
       printf("请输入要发送的数据：");
       scanf("%d",&value);

       int ret = sendto(socketfd, &value, sizeof(value),0,(struct sockaddr*)&dest_addr,sizeof(dest_addr));
       if(ret == -1)
       {
            perror("sendto error");
            break;
       }

       printf("sendto ret:%d\n",ret);
    }
    
    close(socketfd);
 }
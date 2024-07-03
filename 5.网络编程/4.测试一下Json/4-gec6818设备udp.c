#include<stdio.h>
#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define SERVER_IP "192.168.1.160"  //Ubuntu主机服务器端的ip
#define SERVER_PORT 12000          //Ubuntu主机服务器的端口号

#define CLIENT_IP "192.168.1.160"  //我自己这边端的ip
#define CLIENT_PORT 20001          //客户端的端口号


void *thread_recv(void *arg)
{
    //创建套接字
    int udp_recv_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_recv_socket == -1)
    {
        perror("socket");
        return NULL;
    }

    // 设置端口号复用--重复利用
    int opt = 1;
    setsockopt(udp_recv_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in ownAddr;
    ownAddr.sin_family = AF_INET;
    ownAddr.sin_port = htons(CLIENT_PORT);
    ownAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(udp_recv_socket, (struct sockaddr *)&ownAddr, sizeof(ownAddr)) == -1)
    {
        perror("bind");
        close(udp_recv_socket);
        return NULL;
    }

    while (1)
    {
        char buf[1024] = {0};
        struct sockaddr_in addr;
        int addrlen = sizeof(addr);
        ssize_t ret = recvfrom(udp_recv_socket, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &addrlen);
        if (ret == -1)
        {
            perror("recvfrom");
            continue;
        }
        printf("Received: %s\n", buf);
    }

    close(udp_recv_socket);
    return NULL;
}

int main()
{
/*================================发送的开始========================================*/
  
    //1.创建套接字
    int socketfd = socket(AF_INET,SOCK_DGRAM,0);
    if(socketfd == -1)
    {
        perror("socket");
        return -1;
    }

    //绑定发送端的对方的ip和端口
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(SERVER_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    // //2 绑定
    // int ret = bind(socketfd,(struct sockaddr*)&dest_addr,sizeof(dest_addr));
    // if(ret == -1)
    // {
    //     perror("bind error");
      
    // }
/*================================发送的结束========================================*/


/*============接收端代码=========*/
    pthread_t id;
    
    pthread_create(&id,NULL,thread_recv,NULL);
/*============接收端代码end=========*/




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
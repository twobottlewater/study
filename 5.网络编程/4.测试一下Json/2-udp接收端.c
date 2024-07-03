#include<stdio.h>
#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#if 0
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);

函数作用：用于UDP中接收数据
参数：
    sockfd：套接字文件描述符
    buf：接收的数据 存储到buf中
    len：要接收的数据长度
    flags：标志位  0
    dest_addr：发送端的IP地址和端口号
    addrlen：结构体的大小

返回值：成功返回发送的字节数，失败返回-1
#endif 

#define SERVER_IP "192.168.1.2"
#define SERVER_PORT 15000

 int main()
 {
    printf("UDP服务器 IP:%s Port:%d\n",SERVER_IP,SERVER_PORT);

    //1.创建套接字
    int socketfd = socket(AF_INET,SOCK_DGRAM,0);
    if(socketfd == -1)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVER_PORT);
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    //2 绑定
    int ret = bind(socketfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(ret == -1)
    {
        perror("bind error");
        return -1;
    }
    //2 接收数据
    while (1)
    {
       char buf[1024] = {0};
       struct sockaddr_in addr;
       int addrlen = sizeof(addr); //一定要赋值

       int ret = recvfrom(socketfd, buf, sizeof(buf),0,(struct sockaddr*)&addr,&addrlen);
       if(ret == -1)
       {
            perror("recvfrom error");
            break;
       }

       printf("IP:[%s] Port:[%d]recvfrom:%s ret:%d\n",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port), buf,ret);

       //转发数据
    }
    
    close(socketfd);
 }
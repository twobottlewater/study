#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define CLIENT_PORT 10086
#define SERVER_IP "192.168.1.160" // 服务器IP地址
#define MAX_BUF_LEN 1024


int sockfd;

void *myrecvmsg(void *arg) 
{
    char buffer[MAX_BUF_LEN];
    int recv_len;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);


    // 接收服务器响应
    while (1)
    {
        memset(buffer, 0, MAX_BUF_LEN);
        recv_len=recvfrom(sockfd,buffer,MAX_BUF_LEN,0,(struct sockaddr *)&addr,&addr_len); 
        //表示接收信息，同时把发送信息的那个主机的信息存储
        //printf("Received: %s\n", buffer);
        printf("服务器给我发送的信息是: %s recvfrom返回值跟recv是不一样的 %d\n",buffer,recv_len);
        // 打印发送方的地址和端口号
        char sender_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(addr.sin_addr), sender_ip, INET_ADDRSTRLEN);
        printf("发送方IP地址: %s, 端口号: %d\n", sender_ip, ntohs(addr.sin_port));
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() 
{
 
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    bzero(&server_addr, sizeof(server_addr));
    char message[MAX_BUF_LEN];
    ssize_t send_len;

    // 创建UDP套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // 初始化服务器地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr= inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);
    

    //初始化客户端地址结构(自己的)
    client_addr.sin_family = AF_INET;//网络协议栈选择
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_addr.sin_port = htons(CLIENT_PORT);

    //绑定自己的地址结构体到套接字
    bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) ;
    //绑定之后，客户端的地址信息就确定了

    //创建一个线程专门接收信息
    pthread_t id;
	pthread_create(&id,NULL,myrecvmsg,NULL);

    // 发送数据到服务器
    while (1)
    {
        /* code */
        printf("输入发送给服务器的消息: ");
        if (fgets(message, MAX_BUF_LEN, stdin) != NULL) {
            size_t len = strlen(message);
            if (len > 0 && message[len - 1] == '\n') {
                message[len - 1] = '\0';
            }
        send_len = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        if (send_len < 0)
        {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }
    }
    }
    // 关闭套接字
    close(sockfd);
    return 0;
   
}
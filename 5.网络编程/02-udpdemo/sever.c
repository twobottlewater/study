#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define CLIENT_PORT 10086
#define CLIENT_IP "192.168.1.160"
#define MAX_BUF_LEN 1024


int sockfd;
struct sockaddr_in client_addr;
int addr_len=sizeof(client_addr);

void *sever_recvmsg(void *arg) 
{
    char buffer[MAX_BUF_LEN];
    int recv_len;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    int send_len;


    // 接收服务器的消息
    while (1)
    {
        memset(buffer, 0, MAX_BUF_LEN);
        recv_len=recvfrom(sockfd,buffer,MAX_BUF_LEN,0,(struct sockaddr *)&addr,&addr_len); 
        //printf("Received: %s\n", buffer);
        printf("客户端给我发送的信息是: %s recvfrom返回值跟recv是不一样的 %d\n",buffer,recv_len);
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
   
    char buffer[MAX_BUF_LEN];
    
    ssize_t recv_len, send_len;

    // 创建UDP套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 初始化服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);


    //初始化客户端地址结构
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(CLIENT_IP);
    client_addr.sin_port = htons(CLIENT_PORT);

    // 绑定套接字到端口
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed"); 
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    //创建一个线程专门接收信息
    pthread_t id;
	pthread_create(&id,NULL,sever_recvmsg,NULL);

    printf("UDP server up and running on port %d\n", PORT);

    while (1) 
    {
        
        printf("请输入要发送给客户端的数据: ");
        fgets(buffer, MAX_BUF_LEN, stdin);
        recv_len = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, addr_len);
        if (recv_len < 0) {
            perror("recvfrom failed");
            continue;
        }


    }

    // 关闭套接字
    close(sockfd);
    return 0;
}
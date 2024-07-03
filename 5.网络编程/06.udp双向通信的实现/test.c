#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define MAX_BUF_LEN 1024

int sockfd;
struct sockaddr_in client_addr;
socklen_t addr_len = sizeof(client_addr);

void *sever_recvmsg(void *arg) 
{
    char buffer[MAX_BUF_LEN];
    ssize_t recv_len;

    // 接收客户端消息
    while (1)
    {
        recv_len = recvfrom(sockfd, buffer, MAX_BUF_LEN, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (recv_len < 0)
        {
            perror("recvfrom failed");
            continue;
        }
        buffer[recv_len] = '\0'; // 确保字符串终止
        printf("收到客户端发来的数据是: %s\n", buffer);
        
        // 向客户端发送响应
        snprintf(buffer, MAX_BUF_LEN, "服务器已收到你的消息: %s", buffer);
        ssize_t send_len = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, addr_len);
        if (send_len < 0) {
            perror("sendto failed");
        }
    }
    pthread_exit(NULL);
}

int main() 
{
    struct sockaddr_in server_addr;
    char buffer[MAX_BUF_LEN];

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

    // 绑定套接字到端口
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 创建一个线程专门接收信息
    pthread_t id;
    pthread_create(&id, NULL, sever_recvmsg, NULL);

    printf("UDP server up and running on port %d\n", PORT);

    // 主线程可以处理其他逻辑或保持空闲
    while (1) {
        // 这里可以添加其他处理逻辑，例如日志记录等
        sleep(1);
    }

    // 关闭套接字
    close(sockfd);
    return 0;
}

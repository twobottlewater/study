#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
  // 创建套接字
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(-1);
  }

  // 连接服务器
  struct sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(8080);

  if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
    perror("connect");
    exit(-1);
  }

  // 与服务器通信
  char buffer[1024];

  while (true) {
    cout << "请输入要发送的消息：";
    cin.getline(buffer, sizeof(buffer));

    int n = send(sockfd, buffer, strlen(buffer) + 1, 0);
    if (n < 0) {
      perror("send");
      break;
    }

    n = recv(sockfd, buffer, sizeof(buffer), 0);
    if (n == 0) {
      break;
    } else if (n < 0) {
      perror("recv");
      break;
    }

    cout << "收到服务器端消息：" << buffer << endl;
  }

  // 关闭连接
  close(sockfd);

  return 0;
}

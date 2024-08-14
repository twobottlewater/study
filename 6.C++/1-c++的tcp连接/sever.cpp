#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
  // 创建套接字
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(-1);
  }

  // 绑定地址和端口号
  struct sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(8080);

  if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
    perror("bind");
    exit(-1);
  }

  // 监听连接
  if (listen(sockfd, 5) < 0) {
    perror("listen");
    exit(-1);
  }

  // 接受连接
  struct sockaddr_in cliaddr;
  socklen_t clilen = sizeof(cliaddr);
  int connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
  if (connfd < 0) {
    perror("accept");
    exit(-1);
  }

  // 与客户端通信
  char buffer[1024];
  while (true) {
    int n = recv(connfd, buffer, sizeof(buffer), 0);
    if (n == 0) {
      break;
    } else if (n < 0) {
      perror("recv");
      break;
    }

    cout << "收到客户端消息：" << buffer << endl;

    string msg = "服务器端回复：" + string(buffer);
    n = send(connfd, msg.c_str(), msg.size(), 0);
    if (n < 0) {
      perror("send");
      break;
    }
  }

  // 关闭连接
  close(connfd);
  close(sockfd);

  return 0;
}

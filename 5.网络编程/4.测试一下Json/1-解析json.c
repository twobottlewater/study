#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "cJson.h"

int main()
{
    //1 打开文件
    int fd = open("./1.json",O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }
    //2 读取数据
    char buf[1024] = {0};
    read(fd,buf,sizeof(buf));
    //3 关闭文件
    close(fd);

    //4 解析数据
    // 将普通的文本数据 转成json对象 
    cJSON *root = cJSON_Parse(buf);

    //根据键reason 得到值
    cJSON *reason = cJSON_GetObjectItem(root,"reason");

    printf("reason = %s\n",reason->valuestring);

    //根据键result 得到值 
    cJSON *result = cJSON_GetObjectItem(root,"result");

    //根据键 data 得到值
    cJSON *data = cJSON_GetObjectItem(result,"data");

    //根据键 conclusion 得到值 
    cJSON *conclusion = cJSON_GetObjectItem(data,"conclusion");

    printf("conclusion = %s\n",conclusion->valuestring);
}

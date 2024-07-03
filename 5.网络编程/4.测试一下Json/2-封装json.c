#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdbool.h>

#include "cJson.h"

/*
{
    "name":"zhang3",
    "age":18,
    "sex":"man",
    "select":false,
    "hobby":["game","sleep","eat"]
}
 */

int main()
{
    //1 先创建一个 json对象 --链表的头节点
    cJSON *root = cJSON_CreateObject();

    //"name":"zhang3" 
    cJSON_AddStringToObject(root,"name","zhang3");

    //"age":18,
    cJSON_AddNumberToObject(root,"age",18);

    // "sex":"man",
    cJSON_AddStringToObject(root,"sex","man");

    // "select":false,
    cJSON_AddBoolToObject(root,"select",false);

    // "hobby":["game","sleep","eat"]
    cJSON *hobby = cJSON_CreateArray();
    cJSON_AddItemToArray(hobby,cJSON_CreateString("game"));
    cJSON_AddItemToArray(hobby,cJSON_CreateString("sleep"));
    cJSON_AddItemToArray(hobby,cJSON_CreateString("eat"));

    cJSON_AddItemToObject(root,"hobby",hobby);

    //2 把json对象转换成json格式的字符串
    char *out = cJSON_Print(root);

    printf("out = %s\n",out);

    //3 把json格式的字符串写入到文件中
    int fd = open("./2.json",O_CREAT|O_WRONLY|O_TRUNC,0666);
    
    if(fd == -1)
    {
        perror("open");
        return -1;
    }

    write(fd,out,strlen(out));

    close(fd);
    return 0;
}
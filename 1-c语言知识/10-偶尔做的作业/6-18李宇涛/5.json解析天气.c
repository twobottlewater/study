#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "cJson.h"

#if 0
(cJSON *) cJSON_GetObjectItem(const cJSON * const object, const char * const string);
函数作用：根据 键  得到值 
#endif 

int main()
{
    //1 打开文件
    int fd = open("weather.json",O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }
    //2 读取数据
    char data[1024*10] = {0};
    read(fd,data,sizeof(data));

    //3 json解析 
    //3.1将普通的数据 转换成json格式的数据 --json对象
    //7 获取下来的数据先由json解析数据
    cJSON *root = cJSON_Parse(data);

    //7.1匹配数据
    cJSON *showapi_res_body = cJSON_GetObjectItem(root,"showapi_res_body");    //获取下来的是一个数组

    cJSON *hourList = cJSON_GetObjectItem(showapi_res_body,"hourList");

    int len = cJSON_GetArraySize(hourList);    //得知长度便于遍历
    printf("%d\n",len);

    for (int i = 0; i < len; i++)
    {
        //数组中的每个元素
        cJSON *item = cJSON_GetArrayItem(hourList,i);
    
        //解析
        //time
        char *item_time = cJSON_GetObjectItem(item,"time")->valuestring;
        //wind_direction
        char* item_wind = cJSON_GetObjectItem(item,"wind_direction")->valuestring;
        //wind_power
        char* item_wind_power = cJSON_GetObjectItem(item,"wind_power")->valuestring;
        //areaid
        char* item_areaid = cJSON_GetObjectItem(item,"areaid")->valuestring; 
        //temperature
        char* item_temperature = cJSON_GetObjectItem(item,"temperature")->valuestring; 
        //area
        char* item_area = cJSON_GetObjectItem(item,"area")->valuestring; 
        //weather
        char* item_weather = cJSON_GetObjectItem(item,"weather")->valuestring; 
        

        printf("时间: %s, 风向 :%s, 风力 :%s, 地区id :%s, 温度 :%s, 地区 :%s, 天气 :%s\n",item_time,item_wind,item_wind_power,item_areaid,item_temperature,item_area,item_weather);
    }

    //5 关闭文件
    close(fd);
}
#include <stdio.h>

#if 0
    int fprintf(FILE *stream, const char *format, ...);
#endif 
int main()
{
    // 打开文件
    FILE *fp = fopen("test.txt", "w");
    if(fp == NULL)
    {
        perror("fopen");
        return 1;
    }
    //将指定格式的数据写入到文件中 fprintf
    fprintf(fp,"%s %s %d %d %f\n",
                    "440828199907082222",
                    "li4",
                    2024100102,
                    23,
                    100.0);



    fclose(fp);
    return 0;
}
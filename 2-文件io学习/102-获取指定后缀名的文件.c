#include <sys/types.h> 
#include <dirent.h>
#include <string.h>
#include <stdio.h>
 
int main() {
    //1、打开目录文件
    DIR *dir = opendir("./aa");
    if(dir == NULL) {
        perror("opendir");
        return -1;
    }
    //2、读取目录中的目录项
    while(1)
    {
        struct dirent *info = readdir(dir);
        if(info == NULL) {
            break;
        }
        if(info->d_type == DT_REG)//判断是一个普通文件
        {
            //判断文件名后缀是.bmp
            char suffix[] = ".bmp";
            if(strstr(info->d_name,suffix) != NULL)
            {
                printf("i-node:%lu 文件类型:%hhu 文件名:%s\n",info->d_ino,info->d_type,info->d_name);  
            }  
        }
    }

    //3、关闭目录文件
    closedir(dir);
}
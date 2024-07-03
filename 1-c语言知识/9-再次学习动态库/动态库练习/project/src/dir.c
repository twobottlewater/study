#include "dir.h"


DNode_t* dir_searchToList(const char*dirName,const char*suffix)
{
    //创建一条链表
    DNode_t*list = list_init();

    //1、打开目录文件
    DIR *dir = opendir(dirName);
    if(dir == NULL) {
        perror("opendir");
        return NULL;
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
            //判断文件名后缀
            int len = strlen(info->d_name);
            if(info->d_name[len-4] == suffix[0] &&
               info->d_name[len-3] == suffix[1] &&
               info->d_name[len-2] == suffix[2] &&
               info->d_name[len-1] == suffix[3])
            {
                //printf("i-node:%lu 文件类型:%hhu 文件名:%s\n",info->d_ino,info->d_type,info->d_name);  
                char pathName[1024] = {0};
                sprintf(pathName,"%s/%s",dirName,info->d_name);
                //printf("文件名:%s\n",pathName);

                //插入链表中
                DElemType_t data;
                memset(&data,0,sizeof(data));
                strcpy(data.fileName,pathName);

                list_insert_tail(list,data);
            }  
        }
    }

    //3、关闭目录文件
    closedir(dir);

    list_show(list);

    return list;
}
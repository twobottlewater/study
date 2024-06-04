#include "myhead.h"
#include "file_list.h"
#include "file_utils.h"



int main(int argc, char **argv)
{
   
    if (argc < 2) {
        fprintf(stderr, "使用方法: %s <目录路径>\n", argv[0]);
        return 1;
    }
    FileNode *file_list = NULL;
     // 调用刚才写的递归函数
    myreaddir(argv[1],&file_list);
    print_list(file_list);
    free_list(file_list);
    return 0;
}
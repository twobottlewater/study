#include "file_utils.h"

// 检查文件是否为 .txt 文件
int is_txt_file(const char *filename) {
    const char *dot = strrchr(filename, '.');
    return dot && strcmp(dot, ".txt") == 0;
}

// 封装一个递归函数
int myreaddir(const char *dirpath, FileNode **file_list) {
    DIR *mydir;
    char allpath[512] = {0}; // 增加缓冲区大小
    // 打开目录
    mydir = opendir(dirpath);
    if (mydir == NULL) {
        perror("打开目录失败了!\n");
        return -1;
    }

    // 循环读取目录
    struct dirent *mydirent;
    while ((mydirent = readdir(mydir)) != NULL) {
        // 排除掉.和..
        if (strcmp(mydirent->d_name, ".") == 0 || strcmp(mydirent->d_name, "..") == 0)
            continue;

        // 判断文件类型
        if (mydirent->d_type == DT_REG && is_txt_file(mydirent->d_name)) { // 只处理 .txt 文件
            // 拼接得到文件的绝对路径
            snprintf(allpath, sizeof(allpath), "%s/%s", dirpath, mydirent->d_name);
            add_node(file_list, allpath);
        } else if (mydirent->d_type == DT_DIR) { // 目录
            // 拼接得到目录的绝对路径
            snprintf(allpath, sizeof(allpath), "%s/%s", dirpath, mydirent->d_name);
            myreaddir(allpath, file_list);
        }
    }
    closedir(mydir);
    return 0;
}

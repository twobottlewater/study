#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "file_list.h"

// 声明文件处理相关函数
int is_txt_file(const char *filename);
int myreaddir(const char *dirpath, FileNode **file_list);

#endif // FILE_UTILS_H

#ifndef FILE_LIST_H
#define FILE_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义一个链表类型--单向链表
typedef struct FileNode {
    char file_path[512];
    struct FileNode *next;
} FileNode;

// 声明链表操作函数
FileNode *create_node(const char *file_path);
void add_node(FileNode **head, const char *file_path);
void print_list(FileNode *head);
void free_list(FileNode *head);

#endif // FILE_LIST_H

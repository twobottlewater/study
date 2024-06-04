#include "file_list.h"

// 创建新节点
FileNode *create_node(const char *file_path) {
    FileNode *new_node = (FileNode *)malloc(sizeof(FileNode));
    if (new_node == NULL) {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    strncpy(new_node->file_path, file_path, sizeof(new_node->file_path) - 1);
    new_node->file_path[sizeof(new_node->file_path) - 1] = '\0'; // 确保字符串终止
    new_node->next = NULL;
    return new_node;
}

// 在链表头部添加新节点
void add_node(FileNode **head, const char *file_path) {
    FileNode *new_node = create_node(file_path);
    new_node->next = *head;
    *head = new_node;
}

// 打印链表
void print_list(FileNode *head) {
    FileNode *current = head;
    while (current != NULL) {
        printf("文件路径: %s\n", current->file_path);
        current = current->next;
    }
}

// 释放链表内存
void free_list(FileNode *head) {
    FileNode *current = head;
    while (current != NULL) {
        FileNode *temp = current;
        current = current->next;
        free(temp);
    }
}

#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

// 创建链表节点
ListNode* createNode(int data) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 删除链表中的重复节点
void removeDuplicates(ListNode* head) {
    ListNode* current = head;

    while (current != NULL && current->next != NULL) {
        ListNode* runner = current;

        while (runner->next != NULL) {
            if (runner->next->data == current->data) {
                ListNode* temp = runner->next;
                runner->next = runner->next->next;
                free(temp);
            } else {
                runner = runner->next;
            }
        }

        current = current->next;
    }
}

// 打印链表
void printList(ListNode* head) {
    ListNode* current = head;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    // 创建链表
    ListNode* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(2);
    head->next->next->next->next = createNode(4);
    head->next->next->next->next->next = createNode(1);

    printf("原始链表：");
    printList(head);

    // 删除重复节点
    removeDuplicates(head);

    printf("去重后的链表：");
    printList(head);

    // 释放链表内存
    ListNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

// 定义链表结点结构体
typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

// 创建新结点
ListNode *createNode(int data) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 打印链表
void printList(ListNode *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// 逆置链表
ListNode *reverseList(ListNode *head) {
    ListNode *prev = NULL;
    ListNode *current = head;
    ListNode *next = NULL;

    while (current != NULL) {
        next = current->next; // 保存下一个结点
        current->next = prev;  // 反转指针
        prev = current;        // 移动到下一个结点
        current = next;        // 继续下一个循环
    }
    return prev;
}

int main() {
    // 创建链表：1 -> 2 -> 3 -> 4 -> 5
    ListNode *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    printf("原始链表：");
    printList(head);

    // 逆置链表
    head = reverseList(head);

    printf("逆置后的链表：");
    printList(head);

    // 释放链表内存
    ListNode *temp = head;
    while (temp != NULL) {
        ListNode *next = temp->next;
        free(temp);
        temp = next;
    }

    return 0;
}

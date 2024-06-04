#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义双向循环链表的节点结构体
typedef struct DListNode {
    int data;
    struct DListNode *prev;
    struct DListNode *next;
} DListNode;

// 创建双向循环链表
DListNode *createDList() {
    DListNode *head = (DListNode *)malloc(sizeof(DListNode));

    head->data = 0;
    head->prev = head;
    head->next = head;

    return head;
}

// 插入节点到双向循环链表
void insertNode(DListNode *head, int data) {
    DListNode *newNode = (DListNode *)malloc(sizeof(DListNode));
    newNode->data = data;
    newNode->prev = head;
    newNode->next = head->next;
    head->next->prev = newNode;
    head->next = newNode;
}

// 打印双向循环链表
void printDList(DListNode *head) {
    DListNode *current = head->next;
    printf("双向循环链表：");
    while (current != head) {
        printf("%d ", current->data);
        current = current->next; // 向后移动
    }
    printf("\n");
}

// 交换相邻两个节点
void swapNodes(DListNode *node1, DListNode *node2) {
    node1->prev->next = node2;
    node2->next->prev = node1;

    node1->next = node2->next;
    node2->prev = node1->prev;

    node1->prev = node2;
    node2->next = node1;
}

// 冒泡排序双向循环链表
void bubbleSortDList(DListNode *head) {
    int swapped;
    DListNode *current;
    DListNode *last = NULL;

    if (head->next == head) {
        return; // 链表为空，直接返回
    }

    do {
        swapped = 0;
        current = head->next;

        while (current->next != head) {
            if (current->data > current->next->data) {
                swapNodes(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

int main() {
    DListNode *head = createDList();

    // 插入节点
    insertNode(head, 3);
    insertNode(head, 1);
    insertNode(head, 4);
    insertNode(head, 1);
    insertNode(head, 5);

    printf("排序前：\n");
    printDList(head);

    // 冒泡排序
    bubbleSortDList(head);

    printf("排序后：\n");
    printDList(head);

    return 0;
}

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

// 冒泡排序双向循环链表
void bubbleSortDList(DListNode *head) {
    DListNode *start = head->next;
    DListNode *end = head;
    bool swapped;

    do {
        swapped = false;
        start = start->next;
        end = end->prev;

        while (start != end) {
            if (start->data > start->next->data) {
                int temp = start->data;
                start->data = start->next->data;
                start->next->data = temp;
                swapped = true;
            }
            start = start->next;
        }

        if (!swapped) {
            break; // 如果这一轮没有交换，则排序已完成
        }

        // 移动 end 指针，使其指向当前已排序部分的最末尾
        end = end->prev;
    } while (start != end);
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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义单向链表的节点结构体
typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

// 创建单向链表
ListNode *createList() {
    return NULL;
}

// 插入节点到单向链表尾部
void add_tail(ListNode **head,int newdata)
{
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->data = newdata;
    newNode->next = NULL;
    if (*head == NULL)
    {
        *head = newNode;
        /* code */
    }
    else
    {
        ListNode *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

//打印链表
void printflist(ListNode *head)
{
    printf("单向链表：");
    while (head != NULL)
    {
        printf("%d ",head->data);
        head = head->next;
    }
}

// 冒泡排序单向链表（值交换）
void bubbleSortList(ListNode *head) 
{
    int swapped;
    ListNode *current;
    ListNode *last = NULL;

    if (head == NULL) {
        return; // 链表为空，直接返回
    }

    do {
        swapped = 0;
        current = head;

        while (current->next != last) {
            if (current->data > current->next->data) {
                // 交换相邻节点的值
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}


int main() 
{
   ListNode *head=createList();
    // 插入节点
    add_tail(&head, 3);
    add_tail(&head, 1);
    add_tail(&head, 4);
    add_tail(&head, 1);
    add_tail(&head, 5);

    printf("排序前：\n");
    printflist(head);

    // 冒泡排序
    bubbleSortList(head);

    printf("排序后：\n");
    printflist(head);

    // 释放链表内存
    ListNode *current = head;
    ListNode *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    return 0;

}
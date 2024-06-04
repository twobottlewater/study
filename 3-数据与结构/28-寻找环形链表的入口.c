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



// 检测链表是否存在循环的函数
int has_cycle(struct ListNode *head) {
    struct ListNode *slow = head;
    struct ListNode *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return 1;
        }
    }

    return 0;
}

int main()
{
	 // 创建一个带有循环的链表来测试
    struct ListNode node1 = {1, NULL};
    struct ListNode node2 = {2, NULL};
    struct ListNode node3 = {3, NULL};
    struct ListNode node4 = {4, NULL};
    struct ListNode node5 = {5, NULL};

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node2;  // 创建循环
	int result = has_cycle(&node1);
	
	printf(result ? "链表存在循环\n" : "链表不存在循环\n");

    return 0;
	
}
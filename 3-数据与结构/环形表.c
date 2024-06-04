#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义链表节点结构体
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

bool hasCycle(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next; // 慢指针每次移动一步
        fast = fast->next->next; // 快指针每次移动两步

        if (slow == fast) {
            // 快慢指针相遇，链表中存在环
            return true;
        }
    }

    // 快指针到达末尾，链表中不存在环
    return false;
}


ListNode *detectCycle(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next; // 慢指针每次移动一步
        fast = fast->next->next; // 快指针每次移动两步

        if (slow == fast) {
            // 快慢指针相遇，链表中存在环
            ListNode *ptr1 = head;
            ListNode *ptr2 = slow; // ptr2指向相遇点

            while (ptr1 != ptr2) {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }

            // ptr1和ptr2相遇的位置即为环的起始节点（入环点）
            return ptr1;
        }
    }

    // 快指针到达末尾，链表中不存在环
    return NULL;
}

// 打印展示环形链表的全部内容
void printCycleList(ListNode *head) {
    ListNode *startNode = detectCycle(head);
    if (startNode == NULL) {
        printf("链表中不存在环\n");
        return;
    }

    printf("环的起始节点值为：%d\n", startNode->val);

    ListNode *currentNode = startNode->next;
	  printf("环的全部值为：%d ", startNode->val);
    while (currentNode != startNode) {
        printf("%d ", currentNode->val);
        currentNode = currentNode->next;
    }
    printf("\n");
}

int main() {
    // 创建一个包含环的链表
	ListNode *head = (ListNode*)malloc(sizeof(ListNode));
	ListNode *node2 = (ListNode*)malloc(sizeof(ListNode));
	ListNode *node3 = (ListNode*)malloc(sizeof(ListNode));
	ListNode *node4 = (ListNode*)malloc(sizeof(ListNode));
	ListNode *node5 = (ListNode*)malloc(sizeof(ListNode));
	ListNode *node6 = (ListNode*)malloc(sizeof(ListNode));
	
    head->val = 1;
    node2->val = 2;
    node3->val = 3;
    node4->val = 4;
	node5->val = 5;
	node6->val = 6;

    head->next = node2;
    node2->next = node3;
    node3->next = node4;
	node4->next = node5;
	node5->next = node6;
    node6->next = node2; // 创建环
	ListNode *prt3=detectCycle(head);
    printf("链表是否含有环：");
    if (hasCycle(head)) {
        printf("是\n");
    } else {
        printf("否\n");
    }
	
	printf("展示环形链表的全部内容：\n");
    printCycleList(head);

    // 释放链表节点内存
	free(head);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>



typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;



Node* initList() {
    Node* dummy = (Node*)malloc(sizeof(Node));
    if (dummy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    dummy->data = 0;  // 哨兵节点的数据通常不使用
    dummy->prev = dummy->next = dummy;
    return dummy;
}

void append(Node* head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;

    // 插入到哨兵节点之前
    newNode->next = head;
    newNode->prev = head->prev;
    head->prev->next = newNode;
    head->prev = newNode;
}

int delete(Node* head, int data) {
    Node* current = head->next;
    while (current != head) {  // 遍历链表
        if (current->data == data) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            return 1;  // 删除成功
        }
        current = current->next;
    }
    return 0;  // 未找到数据，删除失败
}


void clearList(Node* head) {
    Node* current = head->next;
    while (current != head) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(head);  // 释放哨兵节点
}

void traverse(Node* head) {
    // 从头节点的下一个节点开始，跳过哨兵节点
    Node* current = head->next;
    while (current != head) { // 回到头节点时停止
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}





int main() {
    Node* myList = initList();

    append(myList, 10);
    append(myList, 20);
    append(myList, 30);
    printf("链表遍历结果: ");
    traverse(myList);  // 输出应为: 10 20 30
    delete(myList, 20);
    printf("删除节点后的链表遍历结果: ");
    traverse(myList);  // 输出应为: 10 30
    clearList(myList);
    return 0;
}

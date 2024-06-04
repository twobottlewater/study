#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int SElemType_t;

struct Queue {
    SElemType_t data;
    struct Queue *next;
};

struct linkQueue {
    struct Queue *first;
    struct Queue *last;
    int size;
};

struct linkQueue *managerQueue;

bool init_queue(int size) {
    managerQueue = calloc(1, sizeof(struct linkQueue));
    if (managerQueue == NULL) {
        return false; // 内存分配失败
    }
    managerQueue->size = size;
    managerQueue->first = NULL;
    managerQueue->last = NULL;
    return true;
}

bool isEmpty() {
    return managerQueue->size == 0;
}

bool enQueue(SElemType_t indata) {
    struct Queue *newnode = malloc(sizeof(struct Queue));
    if (newnode == NULL) {
        return false; // 内存分配失败
    }
    newnode->data = indata;
    newnode->next = NULL;

    if (managerQueue->first == NULL) {
        managerQueue->first = newnode;
        managerQueue->last = newnode;
    } else {
        managerQueue->last->next = newnode;
        managerQueue->last = newnode;
    }
    managerQueue->size++;
    return true;
}

bool leaveQueue(SElemType_t *outdata) {
    if (isEmpty()) {
        printf("isEmpty\n");
        return false;
    }

    *outdata = managerQueue->first->data;
    struct Queue *deNode = managerQueue->first;

    managerQueue->first = managerQueue->first->next;
    deNode = NULL;
    free(deNode);
    managerQueue->size--;
    return true;
}

int main() {
    init_queue(5);

    enQueue(10);
    enQueue(20);
    enQueue(30);
    enQueue(40);

    int data;
	printf("出队数据：");
    while (leaveQueue(&data)) {
        printf("%d\n", data);
    }

    return 0;
}

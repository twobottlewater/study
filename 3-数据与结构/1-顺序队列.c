#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int SElemType_t;

// 队列结构体
struct Queue
{
    SElemType_t *data;
    int size;
    int first;
    int last;
};

// 创建并初始化
bool Queue_init(struct Queue *q, int size)
{
    q->data = calloc(size, sizeof(SElemType_t));
    if (q->data == NULL) {
        return false; // 内存分配失败
    }
    q->size = size;
    q->first = 0;
    q->last = 0;
    return true;
}

// 判断是否为空
bool isEmpty(struct Queue *q)
{
    return q->first == q->last;
}

// 判断是否满了
bool isFull(struct Queue *q)
{
    return (q->last + 1) % q->size == q->first;
}

// 入队
bool enQueue(struct Queue *q, SElemType_t data)
{
    if (isFull(q)) {
        printf("isFull\n");
        return false;
    }
    q->data[q->last] = data;
    q->last = (q->last + 1) % q->size;
    return true;
}

// 出队
bool leaveQueue(struct Queue *q, SElemType_t *outData)
{
    if (isEmpty(q)) {
        printf("isEmpty\n");
        return false;
    }

    *outData = q->data[q->first];
    q->first = (q->first + 1) % q->size;

    return true;
}

int main()
{
    struct Queue q;
    if (!Queue_init(&q, 5)) {
        printf("初始化队列失败\n");
        return 1;
    }

    enQueue(&q, 10);
    enQueue(&q, 20);
    enQueue(&q, 30);
    enQueue(&q, 40);
    // 尝试入队50会导致队列溢出

    // 测试用例
    int data;
    while (leaveQueue(&q, &data)) {
        printf("%d\n", data);
    }

    return 0;
}

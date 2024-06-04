#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "kernel_list.h"

typedef int ElemType_t;

//结构体 ---大结构体
typedef struct {
    ElemType_t data;//数据域
    struct list_head list;//指针域 小结构体
}KernelNode_t;

KernelNode_t* list_init()
{
    //1 申请头节点内存空间
    KernelNode_t *head = malloc(sizeof(KernelNode_t));
    if(head == NULL)
    {
        perror("malloc error");
        return NULL;
    }
    //2 初始化
    INIT_LIST_HEAD(&(head->list));

    //head->list.prev = &(head->list);
    //head->list.next = &(head->list);

    return head;
}

void list_insert_tail(KernelNode_t*head,ElemType_t data)
{
    //1、新建一个结点并且初始化
    KernelNode_t *newNode = malloc(sizeof(KernelNode_t));
    if(newNode == NULL)
    {
        perror("malloc error");
        return ;
    }    
    newNode->data = data;
    INIT_LIST_HEAD(&(newNode->list));    

    //2、尾插
    list_add_tail(&(newNode->list), &(head->list));
}

void list_show(KernelNode_t*head)
{
    /*
    #define list_for_each(pos, head)    for(pos = (head)->next; pos != (head); pos = pos->next)
    */
    struct list_head *pos;
    //for(pos=head->list.next; pos!=&(head->list); pos=pos->next)
    list_for_each(pos, &(head->list))
    {

    }
}

int main()
{
    KernelNode_t*listA = list_init();

    //插入数据
    list_insert_tail(listA,10);
    list_insert_tail(listA,20);
    list_insert_tail(listA,30);
    list_insert_tail(listA,40);

    return 0;
}
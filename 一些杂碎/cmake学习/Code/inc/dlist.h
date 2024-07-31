#ifndef __DLIST_H
#define __DLIST_H

#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef  struct{
    char fileName[256];
}  DElemType_t;

//数据结点
typedef struct node{
    DElemType_t data; //存储数据
    struct node *prev;//存储上一个节点的地址
    struct node *next;//存储下一个节点的地址
}DNode_t;

DNode_t* list_init();
bool isEmpty(DNode_t*head);
void list_insert_tail(DNode_t*head,DElemType_t data);
void list_show(DNode_t*head);
int list_length(DNode_t*head);
void list_insert_head(DNode_t*head,DElemType_t data);
bool list_delete(DNode_t*head,DElemType_t data);
const DNode_t* list_update(DNode_t*head,DElemType_t srcData,DElemType_t updateData);
const DNode_t* list_find(DNode_t*head,DElemType_t findData);

#endif

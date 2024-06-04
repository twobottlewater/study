#ifndef __LIST_H__
#define __LIST_H__

#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char fileName[256];//文件名
}  ElemType_t;

//设计节点的数据类型
typedef struct node{
    ElemType_t data;//存数据
    struct node *next; //存储下一个节点（结构体）的地址
}Node_t;

//每条链表的管理结构体 
typedef struct {
    Node_t *head;//头节点
    int count; //节点的个数
}List_t; 

/*
@函数作用：
    初始化链表
@参数：
    无
@返回值：
    List_t* 链表的地址
*/
List_t* list_init();
/*
@函数作用：
    向链表中插入一个节点
@参数：
    List_t* list 链表的地址
    ElemType_t data 插入节点的数据
@返回值：
    无
*/
void list_insert(List_t*list,ElemType_t data);
/*
@函数作用：
    尾插法
@参数：
    List_t* list 链表的地址
*/
void list_insert_tail(List_t*list,ElemType_t data);
/*
@函数作用：
    显示链表中的所有节点
@参数：
    List_t* list 链表的地址
@返回值：
    无
*/
void list_show(List_t* list);
/*
@函数作用：
    头插法
@参数：
    List_t* list 链表的地址
    ElemType_t data 插入节点的数据
@返回值：
    无
*/
void list_insert_head(List_t*list,ElemType_t data);
/*
@函数作用：
    判断链表是否为空
*/
bool isEmpty(List_t*list);
/*
@函数作用：
    删除链表中的节点
@参数：
    List_t* list 链表的地址
    ElemType_t delData 删除节点的数据
@返回值：
    无
*/
void list_delete(List_t*list,ElemType_t delData);
Node_t* list_find(List_t*list,ElemType_t data);
bool list_update(List_t*list,ElemType_t srcData,ElemType_t updateData);
void list_sort(List_t*list);

#endif
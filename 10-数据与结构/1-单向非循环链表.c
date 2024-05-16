#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef float  ElemType_t;

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


List_t* list_init()
{
    //1、每条链表的管理结构体内存空间
    List_t *list = malloc(sizeof(List_t));
    if(list==NULL)
    {
        perror("malloc error");
        return NULL;
    }
    list->head = NULL;
    list->count = 0;

    //2 申请头节点的内存空间
    list->head = malloc(sizeof(Node_t));
    if(list->head == NULL)
    {
        perror("malloc error");
        return NULL;
    }

    list->head->next = NULL;

    return list;
}

void list_insert_tail(List_t*list,ElemType_t data)
{
    //1、申请一个新的结构体内存空间 --新节点
    Node_t *newNode = malloc(sizeof(Node_t));
    if(newNode == NULL)
    {
        perror("malloc error");
        return ;
    }
    //2、初始化新节点
    newNode->data = data;
    newNode->next = NULL;

    //3、如果刚开始链表是空的
    if(list->count == 0){
        // 头节点的next指针成员 存储这个新节点的地址
        list->head->next = newNode;
    }
    else{//4、如果链表不是空的，那么需要找到链表的尾结点
        //找到尾节点
        Node_t *p = list->head;
        while(1)
        {
            if(p->next == NULL)
            {
                break;    
            }

            //p是结构体指针,p->next 存储下一个节点的地址
            p = p->next;
        }

        //尾结点的Next成员 存储新节点的地址
        p->next = newNode;
    }
    //5、节点的个数+1
    list->count++;
}

void list_show(List_t* list)
{
    if(list->count == 0)
        return;

    Node_t *p =list->head->next;

    while(1)
    {
        printf("%d\t",p->data);

        p = p->next;

        if(p == NULL)
            break;
    }

    printf("\n");
}

void list_insert_head(List_t*list,ElemType_t data)
{
    //1新建节点 并且初始化
    Node_t *newNode = malloc(sizeof(Node_t));
    if(newNode == NULL)
    {
        perror("malloc error");
        return ;
    }
    newNode->data = data;
    newNode->next = NULL;

    //2新建节点的next成员存储  头节点的下一个节点地址
    newNode->next = list->head->next;
    //3头节点的next成员存储 新建节点的地址
    list->head->next = newNode;
    //4节点的数量+1
    list->count++;
}

bool isEmpty(List_t*list)
{
    return list->count == 0;
}

//删除
void list_delete(List_t*list,ElemType_t delData)
{
    printf("%s%d\n",__FUNCTION__,__LINE__);
    //1 如果当前链表是空的，直接返回
    if(isEmpty(list))
    {
        return;
    }
    //2 遍历链表 找到你要删除的节点p 以及它的上一个节点pre
    Node_t *p=list->head->next;
    Node_t *pre=list->head;


    while (1)
    {
        if(p->data == delData)
        {
            break;
        }

        pre = p ;
        p = p->next;
    }

    //3 删除节点的上一个节点pre里面的next成员存储删除节点的下一个节点p->next
    pre->next = p->next;
    //4 释放删除节点p的内存空间
  
    free(p);

    //5 节点的数量--
    list->count--;
}
//如果查到了，返回查到的那个结构体指针
//否则返回NULL
Node_t* list_find(List_t*list,ElemType_t data)
{
    //1、如果链表是空的，直接返回NULL
    if(isEmpty(list))
        return NULL;

    //2、遍历链表，每个节点的data数据与 要查找的数据data进行比较
    Node_t *p = list->head->next;
    while (1)
    {
        /* code */
        if(p->data == data)//如果比较相同，则返回那个节点地址
            return p;

        p = p->next;

        if(p == NULL)
            break;
    }

    //3 最后没有找到 返回NULL
    return NULL;
}

bool list_update(List_t*list,ElemType_t srcData,ElemType_t updateData)
{
    //1 如果链表是空的，直接返回
    if(isEmpty(list))
        return false;

    //2 遍历链表，找到你要更新的那个节点srcData
            
    Node_t *p = list->head->next;
    while (1)
    {
        /* code */
        if(p->data == srcData)//如果找到了，则直接更新
        {
            p->data = updateData;
            return true;
        }

        p = p->next;

        if(p == NULL)
            break;
    }
    
    //3 没有找到 则说明更新失败 false
    return false;
}

int main()
{
    //链表A
    List_t*listA = list_init();
    //链表B
    List_t*listB = list_init();
    //链表C
    List_t*listC = list_init();

    //链表A
    list_insert_tail(listA,10);
    list_insert_tail(listA,20);
    list_insert_tail(listA,30);
    list_insert_tail(listA,40);
    list_insert_tail(listA,50);
    list_insert_tail(listA,60);

    list_show(listA);

    //链表B
    list_insert_tail(listB,56);
    list_insert_tail(listB,56);
    list_insert_tail(listB,99);
    list_insert_tail(listB,97);
    list_insert_tail(listB,45);
    list_insert_tail(listB,22);

    list_show(listB);


    //list_insert_head(68);
    // list_delete(30);

    // list_show();

    // list_delete(10);

    // list_show();

    // list_delete(60);
    // list_show();

    // if(list_find(50) != NULL){
    //     printf("yes\n");
    // }else{
    //     printf("no\n");
    // }

    // list_update(50,55);
    // list_show();
    return 0;
}
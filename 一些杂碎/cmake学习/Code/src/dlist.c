#include "../inc/dlist.h"

//初始化链表
DNode_t* list_init()
{
    //1 申请头节点的内存空间 -链表的头 不存储数据
    DNode_t *head = malloc(sizeof(DNode_t));
    if(head == NULL)
    {
        perror("malloc error");
        return NULL;
    }
    //2 初始化
    head->prev = NULL;
    head->next = NULL;

    return head;
}
bool isEmpty(DNode_t*head)
{
    return head->next == NULL;
}

//尾插法
void list_insert_tail(DNode_t*head,DElemType_t data)
{
    //1 新建一个结点 并且初始化
    DNode_t *newNode = malloc(sizeof(DNode_t));
    if(newNode == NULL)
    {
        perror("malloc error");
        return ;
    }
    newNode->data = data;
    newNode->prev = newNode;
    newNode->next = newNode;

    //2 如果当前链表是空的  从无到有
    if(isEmpty(head)){
        //2.1 头节点的next成员存储新建节点的地址
        head->next = newNode;
    }else{//3 如果当前链表是有节点的  从少到多
        //3.1遍历链表，先找到尾节点p
        DNode_t *p = head->next;
        while (1)
        {
            //尾节点里面的next成员存储了首节点地址
            if(p->next == head->next)
            {
                break;
            }
            p = p ->next;
        }
        
        //3.2尾节点p的next成员存储新建节点的地址
        p->next = newNode;
        //3.3新建节点的prev成员 存储 原来尾节点的地址p
        newNode->prev = p;
        //3.4新的尾节点（新建节点）里面的next成员存储首节点地址
        newNode->next = head->next;
        //3.5 数据的首节点里面的prev成员 存储新的尾节点地址
        head->next->prev = newNode;
    }   
}

void list_show(DNode_t*head)
{
    if(isEmpty(head)){
        return ;
    }

    DNode_t *p = head->next;
    while (1)
    {
        printf("%s\n",p->data.fileName);

        p = p->next;

        if(p == head->next)
            break;
    }

    printf("\n");
}

int list_length(DNode_t*head)
{
    int count = 0;

   if(isEmpty(head)){
        return count;
    } 
    
    DNode_t *p = head->next;
    while (1)
    {
        count++;
        p = p->next;

        if(p == head->next)
            break;
    }

    return count;
}

//头插法
void list_insert_head(DNode_t*head,DElemType_t data)
{
    //1 新建一个结点 并且初始化
    DNode_t *newNode = malloc(sizeof(DNode_t));
    if(newNode == NULL)
    {
        perror("malloc error");
        return ;
    }
    newNode->data = data;
    newNode->prev = newNode;
    newNode->next = newNode;

    //2 如果当前链表是空的  从无到有
    if(isEmpty(head)){
        //2.1 头节点的next成员存储新建节点的地址
        head->next = newNode;
    }else{//3 如果当前链表是有节点的  从少到多
        //3.1尾节点里面的next成员存储新节点的地址
        head->next->prev->next = newNode;
        //3.2新建节点里面的prev成员存储尾节点的地址
        newNode->prev = head->next->prev;
        
        //3.3 新建节点的Next成员存储原来链表的数据首节点
        newNode->next = head->next;
        //3.4 原来链表的数据首节点的 prev成员 存储 新建节点
        head->next->prev = newNode;
        //3.5 头节点head里面的next成员 存储新建节点 ----更新头节点
        head->next = newNode;
    }   
}
//删除节点
bool list_delete(DNode_t*head,DElemType_t data)
{
    if(isEmpty(head)){
        return false;
    }
    //1 先找到你要删除的节点
    DNode_t *p = head->next;
    while (1)
    {
        /* code */
        if(strcmp(p->data.fileName , data.fileName)==0)
        {
            break;
        }
        p = p->next;

        //没找到
        if(p == head->next)
            return false;
    }

    //printf("p->data:%d\n",p->data);
    
    //2 如果删除的节点是 数据的首节点 
    if(strcmp(head->next->data.fileName , p->data.fileName)==0)
    {
        //2.1数据的尾节点里面的next成员 存储 删除节点的下一个节点地址
        head->next->prev->next = p->next;
        //2.2删除节点的下一个节点里面的prev成员存储尾节点地址
        p->next->prev = head->next->prev;
        //2.3 头节点中的next成员 存储 删除节点的下一个节点地址
        head->next = p->next;
        //2.4 释放节点
        free(p);
    }
    else if(p->next == head->next)//删除节点是尾节点
    {
        //删除节点的上一个节点里面的next存储首节点地址
        p->prev->next = head->next;
        //数据的首节点里面的prev成员存储删除节点的上一个节点
        head->next->prev = p->prev;
        //释放
        free(p);
    }
    else
    {//3 中间节点
        // 删除节点的上一个节点中的next成员 存储 删除节点的下一个节点的地址
        p->prev->next = p->next;
        //删除节点的下一个节点中的prev成员 存储 删除节点的上一个节点的地址
        p->next->prev = p->prev;
        //释放
        free(p);
    }
    
}

const DNode_t* list_update(DNode_t*head,DElemType_t srcData,DElemType_t updateData)
{
    if(isEmpty(head))
        return NULL;
    
    //1 遍历链表 找到你要修改的那个结点
    DNode_t*p = head->next;
    while (1)
    {
        /* code */
        if(strcmp(p->data.fileName , srcData.fileName)==0 )
        {
            p->data = updateData;
            return p;//2 如果找到了则修改 返回那个节点
        }

        p = p ->next;

        if(p==head->next)
            break;
    } 

    //3 没有找到则返回NULL
    return NULL;
}

const DNode_t* list_find(DNode_t*head,DElemType_t findData)
{
    if(isEmpty(head))
        return NULL;
    
    //1 遍历链表 找到你要修改的那个结点
    DNode_t*p = head->next;
    while (1)
    {
        /* code */
        if(strcmp(p->data.fileName , findData.fileName)==0 )
        {          
            return p;
        }

        p = p ->next;

        if(p==head->next)
            break;
    } 

    //3 没有找到则返回NULL
    return NULL;
}
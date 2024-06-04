#include "list.h"


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
        printf("%s\t",p->data.fileName);

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
        if(strcmp(p->data.fileName,delData.fileName) == 0)
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
        if(strcmp(p->data.fileName,data.fileName) == 0)//如果比较相同，则返回那个节点地址
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
        if(strcmp(p->data.fileName,srcData.fileName) == 0)//如果找到了，则直接更新
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
/*选择排序*/
void list_sort(List_t*list)
{
    // Node_t *minNode = NULL;

    // for(Node_t*p=list->head->next; p!=NULL; p=p->next)
    // {
    //     //假设 j位置的值是最小的 
    //     minNode = p;

    //     for(Node_t*q=p->next; q!=NULL; q=q->next)
    //     {
    //         if(minNode->data > q->data)  
    //         {
    //             minNode = q; //更新最小值节点
    //         }
    //     }

    //     //交换arr[j]和arr[minIndex]
    //     if(minNode != p)
    //     {
    //         int temp = p->data;
    //         p->data = minNode->data;
    //         minNode->data = temp;
    //     }
    // }
}

#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef  struct{
    int id;//学号
    char name[256]; //姓名
    int age; //年龄
    float score;//分数
}ElemType_t;

//数据结点
typedef struct node{
    ElemType_t data; //存储数据
    struct node *prev;//存储上一个节点的地址
    struct node *next;//存储下一个节点的地址
}Node_t;

//初始化链表
Node_t* list_init()
{
    //1 申请头节点的内存空间 -链表的头 不存储数据
    Node_t *head = malloc(sizeof(Node_t));
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
bool isEmpty(Node_t*head)
{
    return head->next == NULL;
}

//尾插法
void list_insert_tail(Node_t*head,ElemType_t data)
{
    //1 新建一个结点 并且初始化
    Node_t *newNode = malloc(sizeof(Node_t));
    if(newNode == NULL)
    {
        perror("malloc error");
        return ;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    //2 如果当前链表是空的  从无到有
    if(isEmpty(head)){
        //2.1 头节点的next成员存储新建节点的地址
        head->next = newNode;
    }else{//3 如果当前链表是有节点的  从少到多
        //3.1遍历链表，先找到尾节点p
        Node_t *p = head;
        while (1)
        {
            if(p->next == NULL)
            {
                break;
            }
            p = p ->next;
        }
        
        //3.2尾节点p的next成员存储新建节点的地址
        p->next = newNode;
        //3.3新建节点的prev成员 存储 原来尾节点的地址p
        newNode->prev = p;
    }   
}

void list_show(Node_t*head)
{
    if(isEmpty(head)){
        return ;
    }

    Node_t *p = head->next;

    printf("%-13s %-10s %-12s %-10s\n","学号","姓名","年龄","分数");

    while (1)
    {
        printf("%-10d %-10s %-10d %-10.1f\n",
                                    p->data.id,
                                    p->data.name,
                                    p->data.age,
                                    p->data.score);

        p = p->next;

        if(p == NULL)
            break;
    }

    printf("\n");
}

int list_length(Node_t*head)
{
    int count = 0;

   if(isEmpty(head)){
        return count;
    } 
    
    Node_t *p = head->next;
    while (1)
    {
        count++;
        p = p->next;

        if(p == NULL)
            break;
    }

    return count;
}

//头插法
void list_insert_head(Node_t*head,ElemType_t data)
{
    //1 新建一个结点 并且初始化
    Node_t *newNode = malloc(sizeof(Node_t));
    if(newNode == NULL)
    {
        perror("malloc error");
        return ;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    //2 如果当前链表是空的  从无到有
    if(isEmpty(head)){
        //2.1 头节点的next成员存储新建节点的地址
        head->next = newNode;
    }else{//3 如果当前链表是有节点的  从少到多
        //3.1 新建节点的Next成员存储原来链表的数据首节点
        newNode->next = head->next;
        //3.2 原来链表的数据首节点的 prev成员 存储 新建节点
        head->next->prev = newNode;
        //3.3 头节点head里面的next成员 存储新建节点 ----更新头节点
        head->next = newNode;
    }   
}
//删除节点
bool list_delete(Node_t*head,ElemType_t data)
{
    if(isEmpty(head)){
        return false;
    }
    //1 先找到你要删除的节点
    Node_t *p = head->next;
    while (1)
    {
        /* code */
        if(p->data.id == data.id)
        {
            break;
        }
        p = p->next;

        //没找到
        if(p == NULL)
            return false;
    }

    //printf("p->data:%d\n",p->data);
    
    //2 如果删除的节点是 数据的首节点 
    if(head->next->data.id == p->data.id)
    {
        //头节点中的next成员 存储 删除节点的下一个节点地址
        head->next = p->next;
        //释放节点
        free(p);

        head->next->prev = NULL;

        printf("2222222\n");
    }
    else if(p->next == NULL)//删除节点是尾节点
    {
        //删除节点的上一个节点里面的next成员赋值为NULL
        p->prev->next = NULL;
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

const Node_t* list_update(Node_t*head,ElemType_t srcData,ElemType_t updateData)
{
    if(isEmpty(head))
        return NULL;
    
    //1 遍历链表 找到你要修改的那个结点
    Node_t*p = head->next;
    while (p!=NULL)
    {
        /* code */
        if(p->data.id == srcData.id)
        {
            p->data = updateData;
            return p;//2 如果找到了则修改 返回那个节点
        }

        p = p ->next;

        // if(p==NULL)
        //     break;
    } 

    //3 没有找到则返回NULL
    return NULL;
}

const Node_t* list_find(Node_t*head,ElemType_t findData)
{
    if(isEmpty(head))
        return NULL;
    
    //1 遍历链表 找到你要修改的那个结点
    Node_t*p = head->next;
    while (p!=NULL)
    {
        /* code */
        if(p->data.id == findData.id)
        {          
            return p;
        }

        p = p ->next;

        // if(p==NULL)
        //     break;
    } 

    //3 没有找到则返回NULL
    return NULL;
}

int main()
{
    Node_t*headA = list_init();

    ElemType_t s1 = {20221001,"zhang3",22,100};
    list_insert_tail(headA,s1);

    ElemType_t s2 = {20221003,"zhang4",22,100};
    list_insert_tail(headA,s2);

    ElemType_t s3 = {20221022,"li4",23,45};
    list_insert_tail(headA,s3);

    ElemType_t s4 = {20221027,"laowang",26,67};
    list_insert_tail(headA,s4);

    list_show(headA);

    // printf("list_length:%d\n",list_length(headA));

    // list_insert_head(headA,5);
    // list_insert_head(headA,1);

    // list_show(headA);

    // printf("list_length:%d\n",list_length(headA));

    //list_delete(headA,40);
    // if(list_update(headA,30,100)){
    //     printf("修改成功\n");
    // }
    
    // list_show(headA);



    return 0;
}
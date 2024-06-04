#include<stdio.h>
#include <stdlib.h>

//设计节点的数据类型
struct node{
    int data; //数据域
    struct node*next; //指针域
};

struct node *head;//头节点
int count=0;//节点的个数

//初始化链表
void list_init()
{
    //申请头节点的内存空间
    head = malloc(sizeof(struct node));
    if(head == NULL)
    {
        perror("malloc error");
        return ;
    }

    head->data = -1;//这个可以省略 一般头节点不存数据
    head->next = NULL;
}

void list_insert_tail(int data)
{
    //1、申请一个结构体内存空间  --新结点
    struct node*newNode = malloc(sizeof(struct node));
    if(newNode == NULL)
    {
        perror("malloc newNode error");
        return ;
    }
    //2、初始化结构体
    newNode->data = data;
    newNode->next = NULL;

    //从无到有 --第一个数据结点
    if(count == 0){
        head->next = newNode;
    }else{
        //3、遍历链表，找到最后一个结点p
        struct node *p = head;
        while(1)
        {
            //最后一个结点里面的next成员存储NULL
            //则表示当前是最后一个结点
            if(p->next == NULL)
                break;
            
            //问题来了，如何让p往下面走
            p = p->next;
        }
        //4、最后一个结点的next指针存储 新建节点的地址
        p->next = newNode;
    }


    //5、节点的个数+1
    count++;
}
void list_show()
{
    //遍历链表
    struct node*p=head->next;
    for(int i=0; i<count; i++)
    {
        printf("%d\t",p->data);
        p=p->next;
    }
    printf("\n");
}

int main()
{
    list_init();

    //插入数据
    list_insert_tail(10);
    list_insert_tail(20);
    list_insert_tail(30);
    list_insert_tail(40);

    list_show();

    list_insert_tail(50);
    list_insert_tail(60);
    list_insert_tail(70);
    
    list_show();

    return 0;
}
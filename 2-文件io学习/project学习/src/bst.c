#include "bst.h"

//设计BST 的操作集
BitNode_t* bst_insert(BitNode_t *T,TElemType_t data)
{
    //1新建一个结点并且初始化
    BitNode_t *newNode = (BitNode_t *)malloc(sizeof(BitNode_t));
    newNode->data = data;
    newNode->lchild = NULL;
    newNode->rchild = NULL;

    //2如果当前二叉树为空，则新建的这个节点就是整个二叉树的根结点
    if(T == NULL){
        T = newNode;
    }else{
        //如果不是空的，则找到合适的位置插入新节点
        BitNode_t *p = T;
        while (1)
        {
            //如果根节点的数据 大于 新节点的数据
            //说明新节点要插入到左子树
            if(p->data.num > data.num) 
            {
                if(p->lchild == NULL){
                    //说明是插在这里
                    p->lchild = newNode;
                    break;        
                }
                p = p->lchild;
            }
            else if(p->data.num < data.num){
                if(p->rchild == NULL){
                    //说明是插在这里
                    p->rchild = newNode;
                    break;        
                }
                p = p->rchild;                
            }else{
                printf("插入失败，因为该节点已经存在\n");
                break; 
                //注意：二叉树不能存在两个相同的节点
            }
        }
        
    }


    return T;
}

//二叉树的初始化
BitNode_t* bst_init()
{
    // BitNode_t *T = NULL;
    // printf("请输入数据，以-1结束:"); 

    // while (1)
    // {
    //     /* code */
    //     TElemType_t data;
    //     scanf("%d",&data);
    //     if(data == -1){
    //         break;
    //     }

    //     T = bst_insert(T,data);
    // }

    //return T;
}

//二叉树的遍历
//前序遍历  根 左 右 
void bst_preorder(BitNode_t *T)
{
    if(T == NULL)
    {
        return ;
    }

    printf("%-20s %-15s %-10d %-5d %-10.f\n",
                            T->data.id,
                            T->data.name,
                            T->data.num,
                            T->data.age,
                            T->data.score);
    bst_preorder(T->lchild);
    bst_preorder(T->rchild);
}
//中序遍历   左  根 右 
void bst_mid(BitNode_t *T)
{
    if(T == NULL)
    {
        return ;
    }
    bst_mid(T->lchild);
    
    printf("%-20s %-15s %-10d %-5d %-10.f\n",
                            T->data.id,
                            T->data.name,
                            T->data.num,
                            T->data.age,
                            T->data.score);
    
    bst_mid(T->rchild);
}

//后序遍历   左  右   根
void bst_post(BitNode_t *T)
{
    if(T == NULL)
    {
        return ;
    }
    bst_post(T->lchild);
    bst_post(T->rchild);
    printf("%-20s %-15s %-10d %-5d %-10.f\n",
                            T->data.id,
                            T->data.name,
                            T->data.num,
                            T->data.age,
                            T->data.score);
}

BitNode_t* bst_delete(BitNode_t*T,TElemType_t data)
{
    //1、如果T为空，则直接返回
    if(T == NULL){
        return T;
    }
    //2、如果T不为空，则找到要删除的节点p和删除节点的父节点pre 
    //先遍历二叉树，找到要删除的节点 
    BitNode_t *p = T;
    BitNode_t *pre = NULL;

    while (p!=NULL)
    {
        /* code */
        if(p->data.num == data.num){
            break;
        }
        if(data.num < p->data.num)
        {
            //删除的节点数据 小于 当前节点 说明删除节点在左子树
            pre = p; 
            p = p->lchild;
        }
        else if(data.num > p->data.num)
        {
            //删除的节点数据 大于 当前节点 说明删除节点在右子树 
            pre = p; 
            p = p->rchild;
        }      
    }
    //如果没有找到直接返回
    if(p == NULL){
        return T;
    }
    //程序走到这里说明已经找到了
    //删除节点p没有孩子
    if(p->lchild == NULL && p->rchild == NULL)
    {
        //printf("删除节点p没有孩子\n");
        //情况a  p是根结点
        if(p == T)
        {
            free(p); 
            T = NULL;
        }
        else if(p == pre->lchild) //情况b 删除节点p 是左子树
        {
            //printf("删除节点p是左子树\n");
            free(p); 
            pre->lchild = NULL;
        }
        else if(p == pre->rchild) //情况c 删除节点p 是右子树
        {
            free(p); 
            pre->rchild = NULL;
        }
    }
    else if(p->lchild != NULL && p->rchild != NULL) { //删除节点p有两个孩子
        printf("删除节点p有两个孩子\n");
        
        //第一步 找到p的左子树中最大的节点p2和最大节点p2的父节点pre2
        BitNode_t*p2 = p->lchild;
        BitNode_t*pre2 = p;
        while (p2->rchild != NULL)
        {
            /* code */
            pre2 = p2;
            p2 = p2->rchild;
        }
        
        //第二步  根据p2的情况不同 进行 a  b 处理
        //情况a 
        if(p->lchild == p2)
        {
            printf("情况a\n");
            TElemType_t temp = p->data;
            p->data = p2->data;
            p2->data = temp;

            pre2->lchild = p2->lchild;
            free(p2);
        }
        else{ //情况b
            TElemType_t temp = p->data;
            p->data = p2->data;
            p2->data = temp;   

            pre2->rchild = p2->lchild;
            free(p2);    
        }       
    }
    else  //删除节点p有一个孩子
    {
        if(p->lchild !=NULL) //删除节点p有一个左孩子
        {
            //a1 删除节点p是父节点的左孩子
            if(p == pre->lchild)
            {
                pre->lchild = p->lchild;
                free(p);
            }
            //a2 删除节点p是父节点的右孩子
            else if(p == pre->rchild)
            {
                pre->rchild = p->lchild;
                free(p);
            }
            else if(p == T)//a3 删除节点p是根节点
            {
                T = p->lchild;
                free(p);
            }
        }
        else if(p->rchild !=NULL) //删除节点p有一个右孩子
        {
            //b1 删除节点p是父节点的右孩子
            if(p == pre->rchild)
            {
                pre->rchild = p->rchild;
                free(p);
            }
            else if(p==pre->lchild)//b2 删除节点p是父节点的左孩子
            {
                pre->lchild = p->rchild;
                free(p);
            }
            else if(p == T)//b3 删除节点p是根节点
            {
                T = p->rchild;
                free(p);
            }
        }
    }
    

    return T;
}



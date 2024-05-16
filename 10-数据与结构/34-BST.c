#include <stdio.h>
#include <stdlib.h>

//设计BST 的节点数据类型
typedef int TElemType_t;

typedef struct BitNode{
    TElemType_t data;
    struct BitNode *lchild,*rchild;
}BitNode_t;

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
            if(p->data > data) 
            {
                if(p->lchild == NULL){
                    //说明是插在这里
                    p->lchild = newNode;
                    break;        
                }
                p = p->lchild;
            }
            else if(p->data < data){
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
    BitNode_t *T = NULL;
    printf("请输入数据，以-1结束:"); 

    while (1)
    {
        /* code */
        int data;
        scanf("%d",&data);
        if(data == -1){
            break;
        }

        T = bst_insert(T,data);
    }

    return T;
}

//二叉树的遍历
//前序遍历  根 左 右 
void bst_preorder(BitNode_t *T)
{
    if(T == NULL)
    {
        return ;
    }

    printf("%d\t",T->data);
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
    
    printf("%d\t",T->data);
    
    bst_mid(T->rchild);
}

//后序遍历   左  右   根
void bst_last_post(BitNode_t *T)
{
    if(T == NULL)
    {
        return ;
    }
    bst_post(T->lchild);
    bst_post(T->rchild);
    printf("%d\t",T->data);
}

int main()
{
    BitNode_t*T1 = bst_init();
    bst_preorder(T1);
    printf("\n");

    bst_mid(T1);
    printf("\n");

    bst_last_postpost(T1);
    printf("\n");

    return 0;
}
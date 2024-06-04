#ifndef __BST_H
#define __BST_H

#include <stdio.h>
#include <stdlib.h>

//设计BST 的节点数据类型
typedef struct{
    char id[19];//身份证
    char name[256];//姓名
    int  num;//学号
    int age;//年龄
    float score;//分数
} TElemType_t;

typedef struct BitNode{
    TElemType_t data;
    struct BitNode *lchild,*rchild;
}BitNode_t;

BitNode_t* bst_insert(BitNode_t *T,TElemType_t data);
BitNode_t* bst_init();
void bst_preorder(BitNode_t *T);
void bst_mid(BitNode_t *T);
void bst_post(BitNode_t *T);
BitNode_t* bst_delete(BitNode_t*T,TElemType_t data);

#endif 
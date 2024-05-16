#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "bst.h"

BitNode_t* opt_init(BitNode_t *root)
{
    //1 打开文件
    FILE *fp = fopen("./data.txt", "r");
    if (fp == NULL)
    {
        perror("文件打开失败");
        return root;
    }

    //2 读取文件内容
    while(1)
    {
        TElemType_t data;
        memset(&data,0,sizeof(data));

        int ret = fscanf(fp,"%s %s %d %d %f",
                                    data.id,
                                    data.name,
                                    &data.num,
                                    &data.age,
                                    &data.score);
        
        printf("ret:%d\n",ret);
        
        if(feof(fp))
            break;

        if(ret < 5){
            printf("读取文件失败\n");
            break;
        }

        //插入到二叉树中
        root = bst_insert(root, data);
    }

    fclose(fp);

    return root;
}

void opt_add(BitNode_t *root)
{
    
}
void opt_show(BitNode_t *root)
{
    printf("line [%d] %s\n",__LINE__,__FUNCTION__);
    //中序遍历
    bst_mid(root);
}
int main()
{
    //根结点
    BitNode_t *root = NULL;

    //从文件中读取数据，初始化二叉树
    root = opt_init(root);

    while (1)
    {
        int mode = -1;
        printf("请输入模式：[1]信息录入  [2]查看信息:");
        scanf("%d", &mode);

        switch (mode)
        {
        case 1:
            /* code */ //保存到文本中   插入到二叉树中
            break;
        case 2:
            /* code */
            opt_show(root);
            break;        
        default:
            break;
        }
        /* code */
    }
    

}
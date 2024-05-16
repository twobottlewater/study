#include "head.h"
#include "bitree.h"


// 前序遍历二叉树的函数
NODE *preorderTraversal(NODE* root)
 {
    if (root == NULL)
	 {
        return -1; // 基准情况：如果当前节点为空，返回
    }

    printf("%c ", root->data); // 访问根节点
    preorderTraversal(root->lchild); // 递归遍历左子树
    preorderTraversal(root->rchild); // 递归遍历右子树

}

// 中序遍历二叉树的函数
NODE *midTraversal(NODE* root)
 {
    if (root == NULL)
	 {
        return -1; // 基准情况：如果当前节点为空，返回
    }
 	midTraversal(root->lchild); // 递归遍历左子树
    printf("%c ", root->data); // 访问根节点
    midTraversal(root->rchild); // 递归遍历右子树

}

// 后序遍历二叉树的函数
NODE *taliTraversal(NODE* root)
 {
    if (root == NULL)
	 {
        return -1; // 基准情况：如果当前节点为空，返回
    }
	taliTraversal(root->lchild); // 递归遍历左子树
 	taliTraversal(root->rchild); // 递归遍历右子树
    printf("%c ", root->data); // 访问根节点   
	
}


int main()
{
	int i;
	//数组把二叉树的值存放起来
	char buf[50]={'A', 'B', 'C', 'D', 'E', 'F', -1, 'G', 'H', -1, -1, -1, 'I'};
	//定义指针数组存放每个节点的地址
	NODE *otherbuf[strlen(buf)];
	
	//写个循环给每个节点分配堆空间，-1的表示没有节点
	for(i=0; i<strlen(buf); i++)
	{
		if(buf[i]!=-1) //是个有效节点
		{
			otherbuf[i]=malloc(sizeof(NODE));
			otherbuf[i]->data=buf[i];
			otherbuf[i]->lchild=NULL;
			otherbuf[i]->rchild=NULL;			
		}
		else //不是个有效节点
			otherbuf[i]=NULL;
	}
	
	//在写个循环左右孩子关系理顺
	for(i=0; i<strlen(buf)/2; i++)
	{
		if(otherbuf[i]!=NULL)
		{
			otherbuf[i]->lchild=otherbuf[2*i+1];
			otherbuf[i]->rchild=otherbuf[2*i+2];
		}
	}
	
	//在网页中显示二叉树
	draw(otherbuf[0]);
	preorderTraversal(otherbuf[0]);
	printf("\n");
	midTraversal(otherbuf[0]);
	printf("\n");
	taliTraversal(otherbuf[0]);
	printf("\n");
}
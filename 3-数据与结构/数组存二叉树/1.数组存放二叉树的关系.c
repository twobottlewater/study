#include "myhead.h"
#include "bitree.h"

int main()
{
	int i;
	//数组把二叉树的值存放起来
	char buf[50]={'A','B','C','D','E','F','G','H','I','J',-1};
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
	
}
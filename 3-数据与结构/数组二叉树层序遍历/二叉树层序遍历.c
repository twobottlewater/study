#include "myhead.h"
#include "bitree.h"
extern struct seqqueue *myqueue;
extern struct seqqueue *seqqueue_init();
extern int myin_queue(NODE *newdata);
extern int if_empty();
extern NODE *myout_queue();

int main()
{
	int i;
	
	//初始化顺序队列
	myqueue=seqqueue_init();
	
	//数组把二叉树的值存放起来
	char buf[50]={'A','B','C','D','E','F','G','H','I',-1,-1,-1,'J'};
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
	
	//二叉树层序遍历
	//第一步根节点入队
	myin_queue(otherbuf[0]);
	
	//第二步
	while(if_empty()!=-1)
	{
		//出队一个节点
		NODE *ret=myout_queue();
		printf("%c",ret->data);
		
		//把这个节点的左孩子入队
		if(ret->lchild!=NULL)
			myin_queue(ret->lchild);
		
		//把这个节点的右孩子入队
		if(ret->rchild!=NULL)
			myin_queue(ret->rchild);
	}
	
}
#include "myhead.h"

/*
	学习任何链表的操作，你只需要验证三个位置对不对即可
	      头结点
		  中间位置
		  末尾位置
*/
//自定义一个结构体来表示单链表
struct singlelist
{
	//数据域--》存文件的路径名
	char filepath[256];
	//指针域--》存下一个数据在内存中的首地址
	struct singlelist *next;
};

struct singlelist *mylist;

//初始化单链表
int list_init()
{
	//定义指针
	mylist=malloc(sizeof(struct singlelist));
	//指针指向哪里呢？
	mylist->next=NULL; 
}

//往单链表中尾插数据
//把newdata存放到list代表的链表的尾部
int list_add_tail(char *newpath)
{
	//给新的数据(新的节点/结点)分配堆空间
	struct singlelist *newnode=malloc(sizeof(struct singlelist));
	//把newpath存放起来
	strcpy(newnode->filepath,newpath);
	//指针指向哪里呢？
	newnode->next=NULL; 
	//找到链表的尾部
	struct singlelist *p=mylist;
	while(p->next!=NULL)
		p=p->next; //循环结束p就到了尾部
	
	//把刚才的新节点存放到链表的尾部(p的后面)
	p->next=newnode; //赋值翻译成指向
	return 0;
}


//打印遍历单链表
int list_show()
{
	struct singlelist *p=mylist;
	while(p!=NULL)
	{
		//打印当前p指向的那个节点里面的内容
		printf("目前遍历的数据是: %s\n",p->filepath);
		p=p->next; //循环结束p就到了尾部
	}
	return 0;	
}

//封装一个递归函数
int myreaddir(const char *dirpath)
{
	DIR *mydir;
	char allpath[100]={0};
	//打开目录
	mydir=opendir(dirpath);
	if(mydir==NULL)
	{
		perror("打开目录失败了!\n");
		return -1;
	}
	
	//循环读取目录
	struct dirent *mydirent;
	while((mydirent=readdir(mydir))!=NULL)
	{
		//排除掉.和..
		if(strcmp(mydirent->d_name,".")==0 || strcmp(mydirent->d_name,"..")==0)
			continue;
		
		//判断文件类型
		if(mydirent->d_type==DT_REG) //普通文件
		{
			//拼接得到文件的绝对路径
			bzero(allpath,100);
			sprintf(allpath,"%s/%s",dirpath,mydirent->d_name);
			//把路径存放到单链表--》尾插
			list_add_tail(allpath);
		}
		else if(mydirent->d_type==DT_DIR) //目录
		{
			//拼接得到目录的绝对路径
			bzero(allpath,100);
			sprintf(allpath,"%s/%s",dirpath,mydirent->d_name);
			myreaddir(allpath);
		}
	}
	return 0;
}

int main()
{
	//初始化单链表
	list_init();
	
	//调用递归读取目录的函数
	myreaddir("./123");
	
	//验证单链表是否存放了所有的文件路径名
	list_show();
	return 0;
}
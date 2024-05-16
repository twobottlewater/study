#include "myhead.h"
#include "kernel_list.h"  //内核链表相关的头文件

//定义一个内核链表的结构体
//叫做大结构体(宿主结构体)
struct kernellist 
{
	//数据域
	char bmppath[256];
	//指针域--》做个封装,叫做小结构体
	struct list_head mypoint;
};
struct kernellist *myhead;//全局变量


//初始化内核链表--》初始化头节点
struct kernellist *list_init()
{
	struct kernellist *head=malloc(sizeof(struct kernellist));
	//指针域初始化
	INIT_LIST_HEAD(&(head->mypoint));
	return head;
}

//封装一个准备新节点的函数
struct kernellist *list_create_node(char *newpath)
{
	struct kernellist *newnode=malloc(sizeof(struct kernellist));
	//数据域初始化
	strcpy(newnode->bmppath,newpath);
	//指正域初始化
	INIT_LIST_HEAD(&newnode->mypoint);
	return newnode;
	
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
			if(strstr(mydirent->d_name,".bmp")!=NULL){
			//拼接得到文件的绝对路径
			bzero(allpath,100);
			sprintf(allpath,"%s/%s",dirpath,mydirent->d_name);
			//把路径存放到单链表--》尾插

			struct kernellist *newnode=list_create_node(allpath);
			list_add_tail(&(newnode->mypoint),&(myhead->mypoint));
			}

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
	char buf[10];
	//初始化内核链表
	myhead=list_init();
	
	//把图片的路径存放到内核链表
		//调用递归读取目录的函数
	myreaddir("./123");
	//定义小结构体指针来遍历内核链表
	struct list_head *p=&(myhead->mypoint);
	
	while(1)
	{
		bzero(buf,10);
		printf("请输入next或者prev来往后，往前遍历内核链表!\n");
		scanf("%s",buf);
		//判断用户输入的是next还是prev
		if(strcmp(buf,"next")==0) //下一张
		{
			p=p->next; //p往后跳
			//打印p指向的节点里面的内容
			//必须由小结构体指针转换得到大结构体指针
			struct kernellist *bigp=list_entry(p,struct kernellist,mypoint);
			printf("下一张图片是: %s\n",bigp->bmppath);
		}
		if(strcmp(buf,"prev")==0) //上一张
		{
			p=p->prev; //p往前跳
			//打印p指向的节点里面的内容
			//必须由小结构体指针转换得到大结构体指针
			struct kernellist *bigp=list_entry(p,struct kernellist,mypoint);
			printf("上一张图片是: %s\n",bigp->bmppath);
		}
	}
}
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
堆空间：是我们程序员（用户）自己手动申请 手动释放的内存区域

特点：你申请了这块内存之后，就会一直存在  除非你手动释放

手动申请内存：

头文件 
    #include <stdlib.h> 
定义函数 
    void* malloc(size_t size);
参数：
    size: 你要申请内存空间的大小  以字节为单位
返回值：
    成功  void* 你申请成功的内存空间的起始地址
    失败  NULL  

什么时候会出现 失败  内存不够的时候

相关函数 malloc, free, realloc, brk 
头文件 #include <stdlib.h> 
定义函数 void *calloc(size_t nmemb, size_t size);

参数：
    nmemb：你要申请多少块内存
    size：每一块的大小
返回值：
    成功  void* 你申请成功的内存空间的起始地址
    失败  NULL  

#endif 


int main()
{
    //int arr[12];
    //12块，每一块的大小是int 4个字节       48
    int*arr1 = calloc(12,sizeof(int));
    int*arr2 = malloc(48);

    //区别：
    //1 、calloc是按块区分
    //2、 calloc申请空间之后，系统会给你清空内存  ，malloc不会


    free(arr1);
    free(arr2);
    
	return 0;
}
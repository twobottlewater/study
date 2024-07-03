#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 #include <string.h>

#if 0
       #include <sys/msg.h>

       int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
函数作用：用于在消息队列中发送数据
参数：
        msqid：消息队列的ID
        msgp：你要发送的数据  一定是结构体地址
        msgsz：你要发送的数据的大小  --不是结构体大小，而是真正你要发送数据的大小  正文的大小
        msgflg：消息的发送标志 一般为0
返回值：
        成功：0
        失败：-1

       #include <sys/msg.h>

       int msgctl(int msqid, int cmd, struct msqid_ds *buf);
函数的作用：设置或者获取消息队列的属性
参数：
        msqid:消息队列的ID
        cmd: 设置或者获取消息队列的属性
                IPC_STAT:获取消息队列的属性
                IPC_SET:设置消息队列的属性
                IPC_RMID:删除消息队列
                IPC_INFO:获取消息队列的信息
        buf：如果你是想要获取消息队列的属性，那么这个参数就可以把属性作为参数传递出来 ---传出参数       

      

#endif 


struct msgbuf{
    long mtype;//消息的类型
    char mtext[1024];//消息的内容 --正文
};

int main()
{
    //1、申请IPC资源 --得到key值  --文件名
    key_t key = ftok(".", 100);
    if(key == -1)
    {
        perror("ftok");
        return -1;
    }

    //2、根据key值创建消息队列 并且得到消息队列的ID  --文件不存在则创建 文件描述符
    int id = msgget( key,IPC_CREAT|0666);
    if(id == -1)
    {
        perror("msgget");
        return -1;
    }
    printf("key:%x id:%d\n",key,id);

        /* code */
    //3、发送数据
    while(1)
    {
        struct msgbuf msg;
        memset(&msg,0,sizeof(msg));

        msg.mtype = 10;//消息的类型
        
        scanf("%s",msg.mtext);

        int ret = msgsnd(id,&msg,strlen(msg.mtext), 0);  //msgrcv
        if(ret == -1)
        {
            perror("msgsnd");
            return -1;
        }
    }
  
  
   

    //4、销毁消息队列
    //msgctl(id,IPC_RMID,NULL);
    return 0;
}
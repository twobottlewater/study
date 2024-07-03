#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 #include <string.h>

#if 0
#include <sys/msg.h>

       ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);

    函数作用：在消息队列中接收消息
    参数：
        msqid：消息队列的ID
        msgp：用来接收消息的结构体
        msgsz：消息的大小 --正文的大小
        msgtyp：消息的类型
        msgflg：标志位  为0 表示阻塞式接收消息
                       为IPC_NOWAIT 表示非阻塞式接收消息
#endif 


struct msgbuf{
    long mtype;//消息的类型  --这个long类型不能变   而且mtype是写在结构体的第一个成员
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

    while (1)
    {
        /* code */
         //3、接收数据
        struct msgbuf msg;
        memset(&msg,0,sizeof(msg));

        int ret = msgrcv(id,&msg,sizeof(msg.mtext),10,0);
        if(ret == -1)
        {
            perror("msgrcv");
            return -1;
        }

        printf("接收到的消息类型为：%ld 数据为:%s\n",msg.mtype,msg.mtext);
    }
    
   

    //4、销毁消息队列
    msgctl(id,IPC_RMID,NULL);
    return 0;
}
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
enum Color{
   RED = 0x00ff0000, //红色
   GREEN = 0x0000ff00, //绿色
   BLACK = 0x00000000, //黑色
   WHITE = 0x00ffffff, //白色
   BLUE = 0x000000ff, //蓝色
   YELLOW = 0x00ffff00, //黄色
   
};

#if 0
      #include <sys/mman.h>

    //内存映射
    void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
函数作用：将某个文件或者某块物理内存映射到用户的虚拟内存空间中
    参数：
        addr：映射到用户空间的起始地址，一般设置为NULL，由系统自动分配
        length：映射到用户空间的字节数  800*480*4
        prot：映射区的保护属性   映射的内存空间 具备的权限    PROT_READ|PROT_WRITE
            PROT_READ：映射区可读
            PROT_WRITE：映射区可写
        flags：映射标志
            MAP_SHARED：1、映射区对所有进程可见   2、对映射成功的内存空间操作 会直接同步到文件中
            MAP_PRIVATE：映射区对所有进程不可见
        fd：映射的文件描述符 你要映射哪个文件 
        offset：偏移量 一般设置为0
返回值：
        成功返回  映射的起始地址
        失败返回  MAP_FAILED
    //解除内存映射
    int munmap(void *addr, size_t length);





#endif 

int main()
{
    //1、打开液晶屏驱动文件 
    int lcdFd = open("/dev/fb0",O_RDWR);
    if(lcdFd == -1)
    {
        perror("open lcd error");
        return -1;
    }
    //2、液晶屏进行内存映射
    //int*lcd_p = (int*)mmap(NULL, 800*480*4,PROT_READ|PROT_WRITE, MAP_SHARED,lcdFd,0);
    int(*lcd_p)[800] = (int(*)[800])mmap(NULL, 800*480*4,PROT_READ|PROT_WRITE, MAP_SHARED,lcdFd,0);
    if(lcd_p == MAP_FAILED){
        perror("mmap error");
        return -1;
    }
    //后续对lcd_p的操作 就是对液晶屏的操作  int lcd_p[800*480]; int lcd_p[480][800]
    // for(int i=0; i<800*480; i++){
    //     lcd_p[i] = 0x00ffff00;
    // }
    for(int j=0; j<480; j++){
        for(int i=0; i<800; i++){
            lcd_p[j][i] = BLACK;
        }

        usleep(10000); //0.1S
    }


    //3、关闭液晶屏文件
    close(lcdFd);
}
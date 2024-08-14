#ifndef MYSERIAL_H
#define MYSERIAL_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <strings.h>
#include <termios.h>
#include <string.h>

volatile unsigned int cardid ;
struct timeval timeout;
class myserial
{
public:
    myserial();
    //打开串口
    int open_serial();
    //配置串口
    void init_tty();
    //发送A命令
    int PiccRequest();
    //发送B命令
    int PiccAnticoll();
private:
    int fd; //串口的文件描述符
};

#endif // MYSERIAL_H

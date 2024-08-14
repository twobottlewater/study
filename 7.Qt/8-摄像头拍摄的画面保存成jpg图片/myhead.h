#ifndef _MYHEAD_H
#define _MYHEAD_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>        //跟perror有关的头文件
#include <sys/mman.h>     //跟内存映射有关的头文件
#include <linux/input.h>  //跟输入子系统模型有关的头文件
#include <linux/videodev2.h> //跟V4L2架构有关的头文件
#endif
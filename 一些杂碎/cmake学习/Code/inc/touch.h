#ifndef __TOUCH_H
#define __TOUCH_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <linux/fb.h>

#include <linux/input.h>//触摸屏的头文件


int touch_wait(int *x, int *y);

#endif 
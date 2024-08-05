#ifndef __RFID_H__
#define __RFID_H__

#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <termios.h> 
#include <sys/types.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#define DEV_PATH   "/dev/ttySAC2"
volatile unsigned int cardid ;
// unsigned int buf[6] ;
struct timeval timeout;

void init_tty(int fd);
unsigned char CalBCC(unsigned char *buf, int n);
int PiccRequest(int fd);
int PiccAnticoll(int fd);


#endif
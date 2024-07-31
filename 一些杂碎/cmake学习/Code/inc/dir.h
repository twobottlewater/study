#ifndef __DIR_H
#define __DIR_H

#include <sys/types.h> 
#include <dirent.h>
#include <string.h>
#include <stdio.h>
 
#include "dlist.h"

DNode_t* dir_searchToList(const char*dirName,const char*suffix);

#endif // __DIR_H
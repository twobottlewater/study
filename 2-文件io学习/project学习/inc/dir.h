#ifndef __DIR_H
#define __DIR_H

#include <sys/types.h> 
#include <dirent.h>
#include <string.h>
#include <stdio.h>
 
#include "list.h"

List_t* dir_searchToList(const char*dirName,const char*suffix);

#endif // __DIR_H
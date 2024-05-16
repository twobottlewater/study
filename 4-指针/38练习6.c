#include <stdio.h>
#include <stdlib.h>
    
    char *Names[]=   //指针数组
    {
         "Bill",
         "Sam",
         "Jim",
         "Paul",
         "Charles"
    };
 
    int main()
    {
        int i;
       char **nm=Names;
       for(i=0; i<5; i++)
          printf("%s\n",*nm++);
       
    }
#include <stdio.h>


int main()
{


    char buffer[256]={0};
    char *path="/home/gec";
    int index=10;
    char *suffix=".bmp";

    //"/home/gec/10.bmp"

    sprintf(buffer,"%s/%d%s",path,index,suffix);
    printf("%s\n",buffer);
    return 0;   

}

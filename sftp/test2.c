#include <stdlib.h>
#include<stdio.h>
int main(){
char *symlinkpath = "./";
char actualpath [256];
char *ptr;


ptr = realpath(symlinkpath, NULL);
printf("%s\n",actualpath);
printf("%s\n",ptr);
return 0;
}

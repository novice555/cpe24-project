#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char cp_command[] = "cp -vR "; 
int copy(char *src, char *dest)
{
    int sys;
    char strbuf[2048] = "";
    if(system(NULL)==0)
        exit(EXIT_FAILURE);
    strcat(strbuf, cp_command);
    strcat(strbuf, src);
    strcat(strbuf, " ");
    strcat(strbuf, dest);
    sys = system(strbuf);
    printf("%d\n", sys);
    return 0;
}
int main()
{
    copy("~/project/copy", "~/project/copy1");
    return 0;
}

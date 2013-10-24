#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char cp_command[] = "cp -vfR "; 
int copy(char *src, char *dest)
{
    int sys;
    char strbuf[2048] = "";
    char strout[10240] = "";
    FILE *f;
    if(system(NULL)==0)
        exit(EXIT_FAILURE);
    strcat(strbuf, cp_command);
    strcat(strbuf, src);
    strcat(strbuf, " ");
    strcat(strbuf, dest);
    //sys = system(strbuf);
    f =  popen(strbuf, "r");
    while(fgets(strout, 10000, f)!=NULL)
        printf("%s\n", strout);
    return 0;
}
int main()
{
    copy("~/project/copy", "~/project/copy1");
    return 0;
}

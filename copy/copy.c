#include<stdio.h>
#include<stdlib.h>
#include<string.h>
static int a = 0;
int read(char *directory);
char cp_command[] = "cp -vfR "; 
int copy(char *src, char *dest)
{
    int sys;
    char strbuf[2048] = "";
    char strout[2048] = "";
    FILE *f;
    int k;
    read(src);
    if(system(NULL)==0)
        exit(EXIT_FAILURE);
    strcat(strbuf, cp_command);
    strcat(strbuf, src);
    strcat(strbuf, " ");
    strcat(strbuf, dest);
    //sys = system(strbuf);
    f =  popen(strbuf, "r");
    while(fgets(strout, 2047, f)!=NULL)
    {        
        printf("%s", strout);
        k++;
    }
    if(k==a)
        printf("Success!!\n");
    else
        printf("Fail!!\n");
    return 0;
}
int main()
{
    a = read("/root/project/copy");
    copy("~/project/copy", "~/project/copy1");
    printf("%d\n",a);
    return 0;
}

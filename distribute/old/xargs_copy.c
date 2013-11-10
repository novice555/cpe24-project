#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"
int xargs_copy(char *src_list, char *dst)
{
    int sys;
    char strbuf[MAX_PATH] = "";
    if(system(NULL)==0)
        exit(EXIT_FAILURE);
    sprintf(strbuf, "xargs -a %s cp --parents -frt %s", src_list, dst);
    printf("%s\n", strbuf);
    sys = system(strbuf);
    if(sys != 0)
        fprintf(stderr, "System Execute Error: Code %d.\n", sys);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"
int rsync_copy(char *src_list, char *src, char *dst)
{

    int sys;
    char strbuf[MAX_PATH] = "";
//    FILE *rsync_open;
//    char buff[512];
/*
    if(system(NULL)==0)
        exit(EXIT_FAILURE);
*/
    sprintf(strbuf, "rsync -as --files-from=%s %s %s", src_list, src, dst);
    printf("%s\n", strbuf);
//    rsync_open = popen(strbuf, "r");
    sys = system(strbuf);
    if(sys != 0)
        fprintf(stderr, "System Execute Error: Code %d.\n", sys);
//    while(fgets(buff, sizeof(buff), rsync_open)!=NULL)
//        printf("%s", buff);
    return 0;
}


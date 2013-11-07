#include<string.h>
#include<stdlib.h>
#include"include/distribute.h"
#include<stdio.h>
static char CHILD_PATH[] = "/koppae00/child/";
static int xargs_copy(char *src_list, char *dst)
{
    int sys;
    char strbuf[MAX_PATH] = "";
    if(system(NULL)==0)
        exit(EXIT_FAILURE);
    sprintf(strbuf, "xargs -a %s cp -frt %s", src_list, dst);
    printf("%s\n", strbuf);
    sys = system(strbuf);
    if(sys == 0)
        fprintf(stderr, "System Execute Error: Code %d.\n", sys);
    return 0;
}

void copy_to_child(FileSource **Child, FileSourceProperties *ChildCount, int MaxChild)
{
    char src[MAX_PATH];
    char dst[MAX_PATH];
    FILE *tmpFile[MaxChild];
    char tmpFileName[MaxChild][MAX_PATH];
    int i, j, n;
    for(i=0; i<MaxChild; i++)
    {
        sprintf(tmpFileName[i], "tmp%d.txt", i+1);
        tmpFile[i] = fopen(tmpFileName[i], "w");
        n = ChildCount[i]->count;
        for(j=0; j<n; j++)
        {
            fprintf(tmpFile[i], "%s\n", Child[i][j]->path);
        }
        fclose(tmpFile[i]);
        sprintf(dst, "%s0%d", CHILD_PATH, i+1);
        printf("%s\n", dst);
        strcpy(src, tmpFileName[i]);
        xargs_copy(src, dst);
        remove(tmpFileName[i]);
    }   
}


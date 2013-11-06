#include<string.h>
#include<stdlib.h>
#include"include/distribute.h"
#include<stdio.h>
static char cp_command[] = "cp -fR ";
static char CHILD_PATH[] = "/koppae00/child/";
static int copy(char *src, char *dest)
{
    int sys;
    char strbuf[MAX_PATH] = "";
    if(system(NULL)==0)
        exit(EXIT_FAILURE);
    strcat(strbuf, cp_command);
    strcat(strbuf, src);
    strcat(strbuf, " ");
    strcat(strbuf, dest);
    sys = system(strbuf);
    //printf("%d\n", sys);
    return 0;
}

void copy_to_child(FileSource **Child, FileSourceProperties *ChildCount, int MaxChild)
{
    char src[MAX_PATH];
    char dst[MAX_PATH];
    int i, j, n;
    for(i=0; i<MaxChild; i++)
    {
        n = ChildCount[i]->count;
        for(j=0; j<n; j++)
        {
            strcpy(src, Child[i][j]->path);
            sprintf(dst, "%s0%d", CHILD_PATH, i+1);
            copy(src, dst);
        }
    }   
}


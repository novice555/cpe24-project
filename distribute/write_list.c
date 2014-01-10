#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"include/distribute.h"
static const char LIST_PATH[] = "/koppae/child/";
void write_same_list(FileDesc desc, int child)
{
    FileSrc find;
    FILE *samelist;
    char dstname[MAX_PATH];    
    int i;

    for(i=1; i<child+1; i++)
    {
        sprintf(dstname, "%s%02d/dynamic.list", LIST_PATH, i);
        if((samelist = fopen(dstname, "w"))==NULL)
        {
            fprintf(stderr, "Cannot write file: %s", dstname);
            exit(1);
        }
        find = desc->head->next;
        while(find!=NULL)
        {
            fprintf(samelist, "%s%s %lld\n", find->src_path+2, find->filename, find->size);
            find = find->next;
        }
        fclose(samelist);
    }
}

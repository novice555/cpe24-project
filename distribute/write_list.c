#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"include/distribute.h"
void write_list(int child, void *src)
{
    CompactSrc *decompact = (CompactSrc *) src;
    FileDesc *Child = decompact->out;
    FileDesc Same = decompact->same;
    FileSrc find;
    FILE *samelist;
    char dstname[MAX_PATH];    
    int i;

    for(i=1; i<child+1; i++)
    {
        sprintf(dstname, "%s%02d/list/dynamic.list", CHILD_PATH, i);
        if((samelist = fopen(dstname, "w"))==NULL)
        {
            fprintf(stderr, "Cannot write file: %s", dstname);
            exit(1);
        }
        find = Same->head->next;
        while(find!=NULL)
        {
            fprintf(samelist, "%s%s %lld\n", find->src_path+2, find->filename, find->size);
            find = find->next;
        }
        fclose(samelist);
    }
    sprintf(dstname, "%slist/dynamic.list", PARENT_PATH);
    if((samelist = fopen(dstname, "w"))==NULL)
    {
        fprintf(stderr, "Cannot write file: %s", dstname);
        exit(1);
    }
    find = Same->head->next;
    while(find!=NULL)
    {
        fprintf(samelist, "%s%s %lld\n", find->src_path+2, find->filename, find->size);
        find = find->next;
    }
    fclose(samelist);

    for(i=1; i<child+1; i++)
    {
        sprintf(dstname, "%s%02d/list/static.list", CHILD_PATH, i);
        if((samelist = fopen(dstname, "w"))==NULL)
        {
            fprintf(stderr, "Cannot write file: %s", dstname);
            exit(1);
        }
        find = Child[i-1]->head->next;
        while(find!=NULL)
        {
            fprintf(samelist, "%s%s\n", find->src_path, find->filename);
            find = find->next;
        }
        fclose(samelist);
    }
}

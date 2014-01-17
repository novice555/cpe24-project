#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"include/distribute.h"
static void write(FileDesc desc, char *dstname)
{
    FILE *file;
    FileSrc find;
    if((file = fopen(dstname, "w"))==NULL)
    {
        fprintf(stderr, "Cannot write file: %s", dstname);
        exit(1);
    }
    find = desc->head->next;
    while(find!=NULL)
    {
        fprintf(file, "%s %s %lld\n", 
            find->src_path, find->filename, find->size
        );
        find = find->next;
    }
    fclose(file);
}
  
void write_file(int child, void *src)
{
    char dstname[MAX_PATH];
    int i;

    CompactSrc *decompact = (CompactSrc *) src;
    FileDesc *Child = decompact->out;
    FileDesc Same = decompact->same;

    for(i=0; i<child; i++)
    {
        sprintf(dstname, "%s%02d/list/static.file", CHILD_PATH, i+1);
        write(Child[i], dstname);
        sprintf(dstname, "%s%02d/list/dynamic.file", CHILD_PATH, i+1);
        write(Same, dstname);
        
    }
    sprintf(dstname, "%s/list/dynamic.file", PARENT_PATH);
    write(Same, dstname);
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"include/distribute.h"
static void read(FileDesc desc, char *path)
{
    FILE *readfile;
    char filename[MAX_FILENAME], src_path[MAX_PATH], c_size[100];
    long long size;
    char *sEnd;
    struct FileSource tmp_add;
    if((readfile = fopen(path, "r"))==NULL)
    {
        fprintf(stderr, "Cannot read file list: %s\n", path);
        exit(1);
    }
    tmp_add.next = NULL;
    tmp_add.back = NULL;
    while(fscanf(readfile, "%s %s %s", src_path, filename, c_size)!=EOF)
    {
        size = strtoll(c_size, &sEnd, 10);
        tmp_add.src_path = strbuff(src_path, strlen(src_path));
        tmp_add.filename = strbuff(filename, strlen(filename));
        tmp_add.size = size;
        //desc->sum_size += size;
        //desc->count++;
        enqueue(desc, tmp_add);
    }
}
void read_file(int child, void *src)
{
    CompactSrc *decompact = (CompactSrc *) src;
    FileDesc *Child = decompact->out;
    FileDesc Same = decompact->same;
    char readname[MAX_PATH];
    int i;
    for(i=0; i<child; i++)
    {
        sprintf(readname, "%s%02d/list/static.file", CHILD_PATH, i+1);
        read(Child[i], readname);
    }
    sprintf(readname, "%s/list/dynamic.file", PARENT_PATH, i+1);
    read(Same, readname);
    
}

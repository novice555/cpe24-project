#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"include/distribute.h"
void move_same_to_child(int child, void *mv_src)
{
    CompactSrc *mv_decompact = (CompactSrc *) mv_src;
    FileDesc *Mv_Child = mv_decompact->out;
    char *absolute_path = "/koppae/child/01/dynamic/";
    copy_to_child(absolute_path, child, 0, mv_src);
    delete_same_file(child, mv_src);
    
}

void move_child_to_same(int child, void *mv_src)
{
    int i;
    char absolute_path[MAX_PATH];
    CompactSrc *mv_decompact = (CompactSrc *) mv_src;
    FileDesc *Mv_Child = mv_decompact->out;
    CompactSrc cs_compact;
    for(i=0; i<child; i++)
    {
        cs_compact.same = Mv_Child[i];
        sprintf(absolute_path, "/koppae/child/%02d/static/", i+1);
        copy_to_child(absolute_path, child, 1, &cs_compact);
    }
    delete_child_file(child, mv_src);
}

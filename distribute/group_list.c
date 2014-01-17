#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"include/distribute.h"
static void extract(FileDesc src, FileDesc dst, char *path_check)
{
    struct FileSource tmp_queue;
    //int count = 0;
    while(src->head->next!=NULL && 
        !strcmp(path_check, src->head->next->src_path)
    )
    {
        //count++;
        //printf("%d\n", count);
        //if(count==261)
        //    printf("asdasdasd\n");
        tmp_queue = dequeue(src);
        enqueue(dst, tmp_queue);
    }
    
}

void first_group_list(int child, void *src, void *re_src)
{
    CompactSrc *decompact = (CompactSrc *) src;
    CompactSrc *re_decompact = (CompactSrc *) re_src;
    FileDesc *Re_Child = re_decompact->out;
    FileDesc Re_Same = re_decompact->same;
    FileDesc *Child = decompact->out;
    FileDesc Same = decompact->same;
    char tmp_path[MAX_PATH];
    int i;
    int check;

    strcpy(tmp_path, Child[0]->head->next->src_path);
    for(i=0; i<child; i++)
        extract(Child[i], Re_Child[i], tmp_path);
    extract(Same, Re_Same, tmp_path);
    if(!Re_Same->count)
    {
        fprintf(stderr, "Cannot group file list: Same->count = 0.\n");
        error(1);
    }
    for(i=0; i<child; i++)
    {
        if(!Re_Child[i]->count)
            fprintf(stderr, "Cannot group file list: Child[%d]->count = 0.\n", i+1);
    }
 

    
}

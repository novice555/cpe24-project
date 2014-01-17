#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"include/distribute.h"
void mv_init(int child, void *mv_src)
{
    int i;
    char *first = "FIRST";
    CompactSrc *mv_decompact = (CompactSrc *) mv_src;
    FileDesc *Mv_Child;

    Mv_Child = malloc(child*sizeof(FileDesc));
    for(i=0; i<child; i++)
    {
        Mv_Child[i] = malloc(sizeof(struct FileSourceProperties));
        Mv_Child[i]->count = 0;
        Mv_Child[i]->sum_size = 0;
        Mv_Child[i]->head = malloc(sizeof(struct FileSource));
        Mv_Child[i]->head->filename = strbuff(first, strlen(first));
        Mv_Child[i]->head->next = NULL;
        Mv_Child[i]->head->back = NULL;
        Mv_Child[i]->tail = Mv_Child[i]->head;
    }   
    mv_decompact->out = Mv_Child;
}
void re_init(int child, void *re_src)
{
    int i;
    char *first = "FIRST";
    CompactSrc *re_decompact = (CompactSrc *) re_src;
    FileDesc *Re_Child;
    FileDesc Re_Same;

    Re_Same = malloc(sizeof(struct FileSourceProperties));
    Re_Same->count = 0;
    Re_Same->sum_size = -1;
    Re_Same->head = malloc(sizeof(struct FileSource));
    Re_Same->head->filename = strbuff(first, strlen(first));
    Re_Same->head->next = NULL;
    Re_Same->head->back = NULL;
    Re_Same->tail = Re_Same->head;
    
    Re_Child = malloc(child*sizeof(FileDesc));
    for(i=0; i<child; i++)
    {
        Re_Child[i] = malloc(sizeof(struct FileSourceProperties));
        Re_Child[i]->count = 0;
        Re_Child[i]->sum_size = 0;
        Re_Child[i]->head = malloc(sizeof(struct FileSource));
        Re_Child[i]->head->filename = strbuff(first, strlen(first));
        Re_Child[i]->head->next = NULL;
        Re_Child[i]->head->back = NULL;
        Re_Child[i]->tail = Re_Child[i]->head;
    }
    re_decompact->out = Re_Child;
    re_decompact->same = Re_Same;
}

void rearrange(int n_child, int n_diff, void *src)
{
    FileDesc Re_Same;
    FileDesc *Re_Child;
    FileDesc *Mv_Child;

    CompactSrc mv_compact;
    
    CompactSrc re_compact;

    CompactSrc *decompact = (CompactSrc *) src;
    FileDesc *Child = decompact->out;
    FileDesc Same = decompact->same;

    long long max_child_size;
    long long sum_child_size;
    long long child_size;

    int i;
    int check, arr;

    re_init(n_child, &re_compact);
    Re_Child = re_compact.out;
    Re_Same = re_compact.same;
    mv_init(n_child, &mv_compact);
    Mv_Child = mv_compact.out;
    int count[4] = {0,0,0,0};
    long long size[4] = {0,0,0,0};
    int count_same = 0;
    long long size_same = 0;
    read_file(n_child, src);
    FileSrc find;
    while(Child[0]->head->next != NULL)
    {
        check = Same->count;
        first_group_list(n_child, src, &re_compact);
        arr = arrange(n_child, n_diff, &re_compact, &mv_compact);
        //test
            find = Re_Child[0]->head->next;
            for(find = find; find!=NULL; find=find->next)
                printf("%s %s %lld\n",find->src_path, find->filename, find->size);
        for(i=0; i<n_child; i++)
        {
            //find = Re_Child[i]->head->next;
            //for(find = find; find!=NULL; find=find->next)
               // printf("%s %s %lld\n",find->src_path, find->filename, find->size);
            count[i] += Re_Child[i]->count;
            size[i] += Re_Child[i]->sum_size;
            Re_Child[i]->head->next = NULL;
            Re_Child[i]->tail = Re_Child[i]->head;
            Re_Child[i]->count = 0;
            Re_Child[i]->sum_size = 0;
        }
        //find = Re_Same->head->next;
        //for(find = find; find!=NULL; find=find->next)
            //printf("%s %s %lld\n",find->src_path, find->filename, find->size);
        count_same += Re_Same->count;
        size_same += Re_Same->sum_size;
        Re_Same->head->next = NULL;
        Re_Same->tail = Re_Same->head;
        Re_Same->count = 0;
        Re_Same->sum_size = 0;
    }
    //for(i=0; i<n_child; i++)
    
    /*
    if(check!=Re_Same->count)
    {
        if(arr)
            move_same_to_child(n_child, &mv_compact);
        else
            move_child_to_same(n_child, &mv_compact);
        //write_list(n_child, &re_compact);
        //write_file(n_child, &re_compact);
    }  */     
    //re_deinit();
}

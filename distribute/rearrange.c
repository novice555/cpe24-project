#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"include/distribute.h"
#include<limits.h>
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
        Mv_Child[i]->head->size = LLONG_MAX;
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
    Re_Same->sum_size = 0;
    Re_Same->head = malloc(sizeof(struct FileSource));
    Re_Same->head->filename = strbuff(first, strlen(first));
    Re_Same->head->size = LLONG_MAX;
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
        Re_Child[i]->head->size = LLONG_MAX;
        Re_Child[i]->head->next = NULL;
        Re_Child[i]->head->back = NULL;
        Re_Child[i]->tail = Re_Child[i]->head;
    }
    re_decompact->out = Re_Child;
    re_decompact->same = Re_Same;
}

void wr_init(int child, void *wr_src)
{
    int i;
    char *first = "FIRST";
    CompactSrc *wr_decompact = (CompactSrc *) wr_src;
    FileDesc *Wr_Child;
    FileDesc Wr_Same;

    Wr_Same = malloc(sizeof(struct FileSourceProperties));
    Wr_Same->count = 0;
    Wr_Same->sum_size = 0;
    Wr_Same->head = malloc(sizeof(struct FileSource));
    Wr_Same->head->filename = strbuff(first, strlen(first));
    Wr_Same->head->size = LLONG_MAX;
    Wr_Same->head->next = NULL;
    Wr_Same->head->back = NULL;
    Wr_Same->tail = Wr_Same->head;

    Wr_Child = malloc(child*sizeof(FileDesc));
    for(i=0; i<child; i++)
    {
        Wr_Child[i] = malloc(sizeof(struct FileSourceProperties));
        Wr_Child[i]->count = 0;
        Wr_Child[i]->sum_size = 0;
        Wr_Child[i]->head = malloc(sizeof(struct FileSource));
        Wr_Child[i]->head->filename = strbuff(first, strlen(first));
        Wr_Child[i]->head->size = LLONG_MAX;
        Wr_Child[i]->head->next = NULL;
        Wr_Child[i]->head->back = NULL;
        Wr_Child[i]->tail = Wr_Child[i]->head;
    }   
    wr_decompact->same = Wr_Same;
    wr_decompact->out = Wr_Child;
}
static void movequeue(FileDesc a, FileDesc b)
{
    if(b->head->next==NULL)
    {
        fprintf(stderr, "Error: B (2nd argument) queue is empty\n");
        exit(1);
    }
    a->tail->next = b->head->next;
    b->head->back = a->tail;
    a->tail = b->tail;
    a->count += b->count;
    a->sum_size += b->sum_size;
    
    b->head->next = NULL;
    b->tail = b->head;
    b->count = 0;
    b->sum_size = 0;
}
void rearrange(int n_child, int n_diff, void *src)
{
    FileDesc Re_Same;
    FileDesc *Re_Child;
    FileDesc *Mv_Child;
    FileDesc *Wr_Child;
    FileDesc Wr_Same;

    CompactSrc mv_compact;
    CompactSrc re_compact;
    CompactSrc wr_compact;

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
    wr_init(n_child, &wr_compact);
    Wr_Child = wr_compact.out;
    Wr_Same = wr_compact.same;
    int count[4] = {0,0,0,0};
    long long size[4] = {0,0,0,0};
    int count_same = 0;
    long long size_same = 0;
    read_file(n_child, src);
    FileSrc find;

    while(Child[0]->head->next != NULL || Same->head->next != NULL)
    {
        //check = Same->count;
        //printf("*%lld\n,",Re_Same->sum_size);
        first_group_list(n_child, src, &re_compact);
        //printf("%s\n,",Re_Same->head->next->src_path);
        //printf("=== Same [%lld byte] ===\n", Re_Same->sum_size);
        //printf("Total %d files.\n", Re_Same->count);
        
        arr = arrange(n_child, n_diff, &re_compact, &mv_compact);
        //printf("=== Same [%lld byte] ===\n", Re_Same->sum_size);
        //printf("Total %d files.\n", Re_Same->count);
        //test
           // find = Re_Same->head->next;
           // for(find = find; find!=NULL; find=find->next)
           //     printf("%s %s %lld\n",find->src_path, find->filename, find->size);
        for(i=0; i<n_child; i++)
        {
            //find = Re_Child[i]->head->next;
            //for(find = find; find!=NULL; find=find->next)
               // printf("%s %s %lld\n",find->src_path, find->filename, find->size);
            
            count[i] += Re_Child[i]->count;
            size[i] += Re_Child[i]->sum_size;
            if(Re_Child[i]->head->next != NULL)
                movequeue(Wr_Child[i], Re_Child[i]);
            /*
            Re_Child[i]->head->next = NULL;
            Re_Child[i]->tail = Re_Child[i]->head;
            Re_Child[i]->count = 0;
            Re_Child[i]->sum_size = 0;
            */
        }
        //find = Wr_Child[0]->head->next;
        //for(find = find; find!=NULL; find=find->next)
          //  printf("%s %s %lld\n",find->src_path, find->filename, find->size);
        //printf("%lld\n",size_same);
        count_same += Re_Same->count;
        size_same += Re_Same->sum_size;
        if(Re_Same->head->next != NULL)
            movequeue(Wr_Same, Re_Same);
        /*
        Re_Same->head->next = NULL;
        Re_Same->tail = Re_Same->head;
        Re_Same->count = 0;
        Re_Same->sum_size = 0;
        */
    }
    
    write_list(n_child, &wr_compact);
    write_file(n_child, &wr_compact);
    //if(check!=Re_Same->count)
    //{
    
        if(arr)
            move_same_to_child(n_child, &mv_compact);
        else
            move_child_to_same(n_child, &mv_compact);
        //write_list(n_child, &re_compact);
        //write_file(n_child, &re_compact);
    
    //}  
    //re_deinit();
    /*
    printf("===== Rearrange Result =====\n");
    for(i=0; i<n_child; i++)
    {
        printf("=== Child [%lld byte] ===\n", size[i]);
        printf("Total %d files.\n", count[i]);
    }
    printf("=== Same [%lld byte] ===\n", size_same);
    printf("Total %d files.\n", count_same);
    printf("\n\n", count_same);
    */
    printf("\n\n===== Rearrange Result =====\n");
    for(i=0; i<n_child; i++)
    {
        printf("=== Child [%lld byte] ===\n", Wr_Child[i]->sum_size);
        printf("Total %d files.\n", Wr_Child[i]->count);
        Child[i]->sum_size = Wr_Child[i]->sum_size;
        Child[i]->count = Wr_Child[i]->count;
    }
    printf("=== Same [%lld byte] ===\n", Wr_Same->sum_size);
    printf("Total %d files.\n", Wr_Same->count);
    Same->sum_size = Wr_Same->sum_size;
    Same->count = Wr_Same->count;
}

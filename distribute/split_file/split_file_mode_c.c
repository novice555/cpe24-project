#include"../include/distribute.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*
static int qsort_cmpfunc(const void *a, const void *b)
{
    const FileSource *x = (*(FileSource **)a);
    const FileSource *y = (*(FileSource **)b);
    int cmp = strcmp(y->src_path, x->src_path);
    long long cmp_num;
    if(cmp==0)
    {
        cmp_num = y->size - x->size;
        if(cmp_num > 0)
            return 1;
        else if(cmp_num < 0)
            return -1;
        else
            return 0;
    }   
    else
        return cmp;
}
*/

static int min_child(FileDesc *desc, int n)
{
    int i;
    int min_no;
    long long min;
    min_no = 0;
    min = desc[0]->sum_size;
    for(i=1; i<n; i++)
    {
        if(desc[i]->sum_size < min)
        {
            min = desc[i]->sum_size;
            min_no = i;
        }
    }
    return min_no;
}

void split_file_mode_c(int ChildNum, int percent, void *src)
{
    CompactSrc *decompact = (CompactSrc *) src;
    FileDesc Parent = decompact->in;
    FileDesc *Child = decompact->out;
    FileDesc Same = decompact->same;

    int cmin;
    long long max_child_size;
    long long child_size;
    struct FileSource tmp_move;
    
    max_child_size = (long long) ((percent/100.0)*(Parent->sum_size));
    /*
    max_parent = Parent->count;
    for(i=0; i<max_parent; i++)
    {
        tmpParent[i] = &Parent[i];                            
    }
        
    

    qsort(tmpParent, max_parent, sizeof(FileSource *), qsort_cmpfunc);
    
    for(i=0; i<max_parent; i++)
    {
        printf("%s [%ld]\n", tmpParent[i]->src, tmpParent[i]->size);
    }
    */
    child_size = 0;
    while(child_size<max_child_size)
    {
        cmin = min_child(Child, ChildNum);
        tmp_move = dequeue(Parent);
        enqueue(Child[cmin], tmp_move);
        Child[cmin]->count++;
        Child[cmin]->sum_size += tmp_move.size;
        child_size += tmp_move.size;
        //printf("[%ld] %s\n", tmpParent[i]->size, tmpParent[i]->path);
         /*
        child_min_count = ChildCount[child_min_no].count;
        Child[child_min_no][child_min_count] = *tmpParent[count];
        ChildCount[child_min_no].count++;
        ChildCount[child_min_no].sum_size += tmpParent[count]->size;
        childsize += tmpParent[count]->size; count++;
        */
    }
    //find = Parent->head->next;
    while(Parent->head != Parent->tail)
    {
        tmp_move = dequeue(Parent);
        enqueue(Same, tmp_move);
        Same->count++;
        Same->sum_size += tmp_move.size;
    }
    
}


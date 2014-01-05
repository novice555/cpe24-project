#include"../include/distribute.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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

static int min_child(FileSourceProperties *array, int n)
{
    int i;
    int min_no = 0;
    long long min = array[min_no].sum_size;
    for(i=1; i<n; i++)
    {
        if(array[i].sum_size < min)
        {
            min = array[i].sum_size;
            min_no = i;
        }
    }
    return min_no;
}

void split_file_mode_b(int ChildNum, int Same, void *src)
{
    CompactSource *decompact = (CompactSource *) src;
    FileSrc1D Parent = decompact->in;
    FileDesc1D ParentCount = decompact->in_count;
    FileSrc2D Child = decompact->out;
    FileDesc1D ChildCount = decompact->out_count;
    int i;
    int max_parent = ParentCount[0].count;
    int child_min_no = 0;
    int child_min_count;
    FileSource *tmpParent[max_parent];
    for(i=0; i<max_parent; i++)
    {
        tmpParent[i] = &Parent[i];                            
    }

    qsort(tmpParent, max_parent, sizeof(FileSource *), qsort_cmpfunc);
    /*
    for(i=0; i<max_parent; i++)
    {
        printf("%s [%ld]\n", tmpParent[i]->src, tmpParent[i]->size);
    }
    */
    for(i=0; i<max_parent; i++)
    {
        //printf("[%ld] %s\n", tmpParent[i]->size, tmpParent[i]->path);
        child_min_no = min_child(ChildCount, ChildNum);
        child_min_count = ChildCount[child_min_no].count;
        Child[child_min_no][child_min_count] = *tmpParent[i];
        ChildCount[child_min_no].count++;
        ChildCount[child_min_no].sum_size += tmpParent[i]->size;
    }    
    
}


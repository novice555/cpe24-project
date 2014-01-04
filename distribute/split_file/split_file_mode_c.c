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

void split_file_mode_c(int ChildNum, int Same, FileSource *Parent, FileSourceProperties *ParentCount, FileSource **Child, FileSourceProperties *ChildCount, FileSource *ChildSame, FileSourceProperties *ChildSameCount)
{
    int i, count;
    int max_parent = ParentCount[0].count;
    int child_min_no = 0;
    int child_min_count;
    long long max_childsize = (long long) (Same/100.0)*ParentCount[0].sum_size;
    long long childsize;
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
    count = 0;
    childsize = 0;
    while(childsize<max_childsize)
    {
        //printf("[%ld] %s\n", tmpParent[i]->size, tmpParent[i]->path);
        child_min_no = min_child(ChildCount, ChildNum);
        child_min_count = ChildCount[child_min_no].count;
        Child[child_min_no][child_min_count] = *tmpParent[count];
        ChildCount[child_min_no].count++;
        ChildCount[child_min_no].sum_size += tmpParent[count]->size;
        childsize += tmpParent[count]->size; count++;
    }
    
    for(i=count; i<max_parent; i++)
    {
        ChildSame[i-count] = *tmpParent[i];
        ChildSameCount[0].count++;
        ChildSameCount[0].sum_size += tmpParent[i]->size;
    }
    
}


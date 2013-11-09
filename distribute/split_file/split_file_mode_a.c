#include"../include/distribute.h"
#include<stdio.h>
#include<stdlib.h>
static int qsort_cmpfunc(const void *a, const void *b)
{
    return (*((FileSource *)b)).size - (*((FileSource *)a)).size;
}

static int min_child(FileSourceProperties *array, int n)
{
    int i;
    int min_no = 0;
    long min = array[min_no].sum_size;
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

void split_file_mode_a(FileSource *Parent, FileSourceProperties *ParentCount, FileSource **Child, FileSourceProperties *ChildCount, int ChildNum)
{
    int i;
    int max_parent = ParentCount[0].count;
    int child_min_no = 0;
    int child_min_count;
    FileSource *tmpParent[max_parent];
    for(i=0; i<max_parent; i++)
    {
        tmpParent[i] = &Parent[i];                            
    }

    qsort(tmpParent, max_parent, sizeof(FileSource), qsort_cmpfunc);
    
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


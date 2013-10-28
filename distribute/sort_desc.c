#include<stdlib.h>
#include<stdio.h>
#include"distribute.h"
int qsort_cmpfunc(const void *a, const void *b)
{
    return (*((FileSource *)b))->size - (*((FileSource *)a))->size;
}

void sort_desc(FileSource *array, int n)
{
    qsort(array, n, sizeof(FileSource), qsort_cmpfunc);    
}                                                            


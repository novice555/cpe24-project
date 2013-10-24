#include<stdlib.h>
#include<stdio.h>
#include"distribute.h"
int qsort_cmpfunc(const void *a, const void *b)
{
    //FileSource x = (FileSource)a;
    //FileSource y = (FileSource)b;
    //printf("%ld : %ld\n", x->size, y->size);
    return (*((FileSource *)b))->size - (*((FileSource *)a))->size;
    //return 1;
}

void sort_file(FileSource list[], int n)
{
    qsort(list, n, sizeof(FileSource), qsort_cmpfunc);    
}                                                            


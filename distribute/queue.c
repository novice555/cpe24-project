#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"
void enqueue(FileDesc desc, struct FileSource src)
{
    FileSrc new = malloc(sizeof(struct FileSource));
    *new = src;
    desc->tail->next = new;
    new->back = desc->tail;
    desc->tail = new;
}
struct FileSource dequeue(FileDesc desc)
{
    struct FileSource ret_val;
    FileSrc old = desc->head->next;
    desc->head->next = old->next;
    if(old->next!=NULL)
        old->next->back = desc->head;
    else
        desc->tail = old->back;
    ret_val = *(old);
    desc->sum_size -= old->size;
    desc->count--;
    free(old);
    return ret_val;
}


void insert_sort(FileDesc desc, struct FileSource src)
{
    FileSrc find;
    FileSrc new = malloc(sizeof(struct FileSource));
    *new = src;
    find = desc->head->next;
    while((find != NULL) && (find->size > new->size))
        find = find->next;
    if(find)
    {
        new->back = find->back;
        new->next = find;
        find->back->next = new;
        find->back = new;
    }
    else
    {
        desc->tail->next = new;
        new->back = desc->tail;
        desc->tail = new;
    }
 
}

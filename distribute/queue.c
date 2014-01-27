#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"
void enqueue(FileDesc desc, struct FileSource src)
{
    FileSrc new = malloc(sizeof(struct FileSource));
    *new = src;
    new->back = desc->tail;
    new->next = NULL;
    desc->tail->next = new;
    desc->tail = new;
    desc->sum_size += src.size;
    desc->count++;
}
void pushbottom(FileDesc desc, struct FileSource src)
{
    FileSrc new = malloc(sizeof(struct FileSource));
    *new = src;
    if(desc->head->next)
    {
        desc->head->next->back = new;
        new->next = desc->head->next;
        desc->head->next = new;
        new->back = desc->head;
    }
    else
    {
        desc->tail->next = new;
        new->back = desc->tail;
        desc->tail = new;
    }
    desc->sum_size += src.size;
    desc->count++;
 
}
struct FileSource dequeue(FileDesc desc)
{
    struct FileSource ret_val;
    FileSrc old;
    
    if(desc->head == desc->tail)
    {
        fprintf(stderr, "Dequeue empty queue.\n");
        exit(1);
    }

    old = desc->head->next;
    if(old->next)
    {
        old->next->back = desc->head;
        desc->head->next = old->next;
    }
    else
    {
        desc->tail = desc->head;
        desc->head->next = NULL;
    }
    ret_val = *(old);
    ret_val.next = NULL;
    ret_val.back = NULL;
    desc->sum_size -= old->size;
    desc->count--;
    free(old);
    return ret_val;
}

struct FileSource popqueue(FileDesc desc)
{
    struct FileSource ret_val;
    FileSrc old;

    if(desc->head == desc->tail)
    {
        fprintf(stderr, "Popqueue empty queue.\n");
        exit(1);
    }

    old = desc->tail;
    desc->tail = old->back;
    desc->tail->next = NULL;
    ret_val = *(old);
    ret_val.next = NULL;
    ret_val.back = NULL;
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
    {
        if(find->size == new->size)
        {
            if(strcmp(new->filename, find->filename)<0)
                break;
        }
        find = find->next;
    }
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

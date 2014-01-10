#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"include/distribute.h"
static strtype head;
static strtype tail;
void string_init()
{
    strtype new = malloc(sizeof(struct stringtype));
    new->str = malloc(sizeof(char)*10);
    strcpy(new->str,"FIRST");
    new->next = NULL;
    head = new;
    tail = new;
}

static void stradd(char *str)
{
    strtype new = malloc(sizeof(struct stringtype));
    new->str = str;
    tail->next = new;
    tail = new;
}

char* strbuff(char *text, int len)
{
    char *tmp;
    if((tmp = malloc(len * sizeof(char)))==NULL)
    {
        fprintf(stderr, "Cannot malloc string: %s\n", text);
        exit(1);
    }
    strcpy(tmp, text);
    stradd(tmp);
    return tmp;
}

void string_deinit()
{
    strtype old;
    while(head!=NULL)
    {
        old = head;
        head = head->next;
        free(old->str);
        free(old);
    }
}


#include<string.h>
#include<stdio.h>
#include<stdlib.h>
char* strbuff(char *text, int len)
{
    char *tmp;
    if((tmp = malloc(len * sizeof(char)))==NULL)
    {
        fprintf(stderr, "Cannot malloc string: %s\n", text);
        exit(1);
    }
    strcpy(tmp, text);
    return tmp;
}

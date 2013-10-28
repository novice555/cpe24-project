#include"distribute.h"
#include<string.h>
#include<stdlib.h>
void copy_filesource(FileSource b, FileSource a)
{
    b = malloc(sizeof(FileSourceDesc));
    strcpy(b->path, a->path);
           
}

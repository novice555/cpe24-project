#include"distribute.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FileSource fetch_file_detail(char *fullpath)
{
    
    FileSource fs;
    FILE *fp;
    fp = fopen(fullpath, "rb");
 
    if(fp == NULL) 
    {
        fprintf(stderr, "\nFile not found!\n");
    }
    else
    {
        fs = malloc(sizeof(FileSourceDesc));
        fseek(fp, 0L,SEEK_END);
        fs->size = ftell(fp);
        strcpy(fs->path, fullpath);
        fclose(fp);
    }
    
    return fs;
}

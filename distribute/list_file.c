#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"

static long file_size(char *fullpath)
{

    FILE *fp;
    long size;
    fp = fopen(fullpath, "rb");
    if(fp == NULL)
    {
        fprintf(stderr, "\nFile not found!\n");
    }
    else
    {
        fseek(fp, 0L,SEEK_END);
        size = ftell(fp);
        fclose(fp);
    }
    return size;
}

void list_file(char *absolute_path, char *relative_path, FileSource *Parent, FileSourceProperties *ParentCount)
{
    DIR *dir;
    struct dirent *ent;
    struct stat st_buf;
    char nextfile[MAX_PATH];
    char nextpath[MAX_PATH];
    int dirlen;
    int count, size;

    dirlen = strlen(absolute_path);
    dir = opendir(absolute_path);
    while((ent = readdir(dir))!=NULL)
    {
        if(strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0)
        {
            continue;
        }
        if((dirlen + strlen(ent->d_name)) > MAX_PATH)
        {
            fprintf(stderr,"Absolute path is too long: %s/%s", absolute_path, ent->d_name);
            return;
        }
        strcpy(nextfile, absolute_path);
        strcat(nextfile, "/");
        strcat(nextfile, ent->d_name);
        strcpy(nextpath, relative_path);
        strcat(nextpath, "/");
        strcat(nextpath, ent->d_name);
        strcat(nextpath, "/");
        stat(nextfile, &st_buf);
        if(S_ISDIR(st_buf.st_mode))
            list_file(nextfile, nextpath, Parent, ParentCount);
        else
        {   // printf("%s   ", nextfile);
       // printf("size %d\n", read_file1(nextfile));
            count = ParentCount[0].count;
            size = file_size(nextfile);
            strcpy(Parent[count].src, nextfile);
            strcpy(Parent[count].dst_path, nextpath);
            strcpy(Parent[count].filename, ent->d_name);
            ParentCount[0].sum_size += Parent[count].size;
            ParentCount[0].count++;
        }
    }
    closedir(dir);
}

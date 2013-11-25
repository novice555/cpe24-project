#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"
/*
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
*/
static long long file_size(char *path)
{
    struct stat st;
    stat(path, &st);
    return (long long) st.st_size;
}
//static int kuy = 0;

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
        //kuy++;

        if(strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0)
        {
            continue;
        }
        if((dirlen + strlen(ent->d_name)) > MAX_PATH - 1)
        {
            fprintf(stderr,"Absolute path is too long: %s/%s", absolute_path, ent->d_name);
            return;
        }
        strcpy(nextfile, absolute_path);
        strcat(nextfile, ent->d_name);
        //printf("%s\n", nextfile);
        stat(nextfile, &st_buf);
        if(S_ISDIR(st_buf.st_mode))
        {
            strcpy(nextpath, relative_path);
            strcat(nextpath, ent->d_name);
            strcat(nextpath, "/");
            strcat(nextfile, "/");
            list_file(nextfile, nextpath, Parent, ParentCount);
        }
        else
        {   // printf("%s   ", nextfile);
       // printf("size %d\n", read_file1(nextfile));
            count = ParentCount[0].count;
            size = file_size(nextfile);
            //printf("%d\n", kuy);
            Parent[count].src_path = strbuff(relative_path, strlen(relative_path) + 1);
            Parent[count].filename = strbuff(ent->d_name, strlen(ent->d_name) + 1);
            Parent[count].size = size;
            ParentCount[0].sum_size += Parent[count].size;
            ParentCount[0].count++;
        }
    }
    closedir(dir);
}

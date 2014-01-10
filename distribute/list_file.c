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
/*
static long long file_size(char *path)
{
    struct stat st;
    stat(path, &st);
    return (long long) st.st_size;
}
*/
//static int kuy = 0;

void list_file(char *absolute_path, char *workpath, void *src)
{
    CompactSrc *decompact = (CompactSrc *) src;
    FileDesc Parent = decompact->in;
    FileDesc Queue = decompact->queue;
  //  FileSrc new, find;
  //  FileSrc p_tail = Parent.tail;
  //  FileSrc q_tail = Queue.tail;
    DIR *dir;
    struct dirent *ent;
    struct stat st_buf;
    struct FileSource tmpfile;
    char nextfile[MAX_PATH];
    char nextpath[MAX_PATH];
    int dirlen;
    int count, size;
    int worklen;
    
    worklen = strlen(workpath);
    dirlen = strlen(absolute_path);
    dir = opendir(absolute_path);
    
    while((ent = readdir(dir))!=NULL)
    {

        if(strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0)
        {
            continue;
        }
        if((dirlen + strlen(ent->d_name)) > MAX_PATH - 1)
        {
            fprintf(stderr,"Absolute path is too long: %s/%s", absolute_path, ent->d_name);
            return;
        }
        strcpy(nextpath, absolute_path);
        strcat(nextpath, ent->d_name);
        //printf("%s\n", nextfile);
        stat(nextpath, &st_buf);
        if(S_ISDIR(st_buf.st_mode))
        {
            
            strcat(nextpath, "/");
            tmpfile.src_path = NULL;
            tmpfile.filename = strbuff(nextpath, strlen(nextpath));
            tmpfile.size = -1;
            tmpfile.next = NULL;
            tmpfile.back = NULL;
            enqueue(Queue, tmpfile);
            continue;
        }
        else
        {   
            strcpy(nextfile, "./");
            strcat(nextfile, absolute_path + worklen);
            tmpfile.src_path = strbuff(nextfile, strlen(nextfile));
            tmpfile.filename = strbuff(ent->d_name, strlen(ent->d_name));
            tmpfile.size = (long long) st_buf.st_size;
            tmpfile.next = NULL;
            tmpfile.back = NULL;
            //add and sort by size desc
            insert_sort(Parent, tmpfile);
            Parent->sum_size += (long long) st_buf.st_size;
            Parent->count++;
        }
    }
    closedir(dir);
}

#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"


FileSource create_filesource(char *fullpath);
void list_file(char *directory, FileSource *Parent, FileSourceProperties ParentCount)
{
    DIR *dir;
    struct dirent *ent;
    struct stat st_buf;
    char nextfile[MAX_PATH];
    int dirlen;
    int count;

    dirlen = strlen(directory);

    dir = opendir(directory);
    while((ent = readdir(dir))!=NULL)
    {
        if(strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0)
        {
            continue;
        }
        if((dirlen + strlen(ent->d_name)) > MAX_PATH)
        {
            fprintf(stderr,"Absolute path is too long: %s/%s", directory, ent->d_name);
            return;
        }
        strcpy(nextfile, directory);
        strcat(nextfile, "/");
        strcat(nextfile, ent->d_name);
        stat(nextfile, &st_buf);
        if(S_ISDIR(st_buf.st_mode))
            list_file(nextfile, Parent, ParentCount);
        else
        {   // printf("%s   ", nextfile);
       // printf("size %d\n", read_file1(nextfile));
            count = ParentCount->count;
            Parent[count] = create_filesource(nextfile);
            ParentCount->sum_size += Parent[count]->size;
            ParentCount->count++;
        }
    }
    closedir(dir);
}

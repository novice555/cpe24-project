#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>
void read(char *directory)
{
    DIR *dir;
    struct dirent *ent;
    struct stat st_buf;
    char nextfile[1024];
    int dirlen = strlen(directory);

    dir = opendir(directory);
    while((ent = readdir(dir))!=NULL)
    {
        if(strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0)
        {
            continue;
        }
        if((dirlen + strlen(ent->d_name)) > 1024)
        {
            fprintf(stderr,"File name too large: %s/%s", directory, ent->d_name);
            return;
        }
        strcpy(nextfile, directory);
        strcat(nextfile, "/");
        strcat(nextfile, ent->d_name);
        stat(nextfile, &st_buf);
        if(S_ISDIR(st_buf.st_mode))
            read(nextfile);
        else
            printf("%s\n", nextfile);
    }
    closedir(dir);
}
int main(int argc, char *argv[])
{
    char *path = realpath(argv[1], NULL);
    printf("%s\n", path);
    read(path);
}

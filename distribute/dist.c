#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include"distribute.h"

void list_file(char *directory);
void sort_file(FileSource list[], int n);
void split_file(FileSource Parent, int *ParentCount, FileSource Child, int *ChildCount, void (*f)(FileSource, int*, FileSource, int*));

int distribute(char *path, void (*split)(FileSource, int*, FileSource, int*))
{
    FileSource ParentFile[MAX_NUM_FILE];
    FileSource ChildFile[MAX_CHILD][MAX_NUM_FILE];
    int ParentFileCount = 0;
    int ChildFileCount[MAX_CHILD] = {0};
    
    int i = 0;
    char absolute_path[MAX_PATH];
    
    realpath(absolute_path, path);
    printf("Path: %s\n", absolute_path);
    printf("Child: %d\n", child);
    list_file(absolute_path);
    
//    sort_file(ParentFile, FileCount);
    for(i=0; i<FileCount ;i++)
    {
        printf("[%ld] %s\n", SourceFile[i]->size, SourceFile[i]->path);
    }

    send_to_child(n, a);

    return 0;
}


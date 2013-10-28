#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include"distribute.h"

FileSourceProperties init_filesourceproperties();

void list_file(char *directory, FileSource *Parent, FileSourceProperties ParentCount);


void distribute(char *path, int n_child, void (*split_file)(FileSource*, FileSourceProperties, FileSource**, FileSourceProperties*, int))
{
    int i, j;
    char absolute_path[MAX_PATH];

    //create variable store info of file

    //init FileSourceProperties
    ParentFileCount = init_filesourceproperties();
    for(i=0; i<n_child; i++)
    {
        ChildFileCount[i] = init_filesourceproperties();
    }
    //fetch realpath
    realpath(absolute_path, path);
    
    printf("Path: %s\n", absolute_path);
    printf("Child: %d\n", n_child);
    //listfile in directory (recursive)
    list_file(absolute_path, ParentFile, ParentFileCount);         

    //function pointer split file to each child
    (*split_file)(ParentFile, ParentFileCount, ChildFile, ChildFileCount, n_child);

    //send file to child
    //send_to_child(ChildFile, ChildFileCount);  

    
    //debug
    /*
    for(i=0; i<FileCount ;i++)
    {
        printf("[%ld] %s\n", SourceFile[i]->size, SourceFile[i]->path);
    }
    */
    for(i=0; i<n_child; i++)
    {
        printf("=== Child [%d] ===", i);
        int count = ChildFileCount[j]->count;
        for(j=0; j<count; j++)
        {
            printf("[%ld] %s\n", ParentFile[j]->size, ParentFile[j]->path);
        }
    }
    return 0;
}


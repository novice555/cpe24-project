#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"include/distribute.h"


//Variable store detail of each file.

static FileSource *ParentFile;
static FileSourceProperties ParentFileCount;
static FileSource **ChildFile;
static FileSourceProperties *ChildFileCount;

//Function init file

static void init_dist(int child)
{
    int i;
    ParentFile = malloc(MAX_NUM_FILE * sizeof(FileSource));
    ChildFile = malloc(child * sizeof(FileSource*));
    for(i=0; i<child; i++)
    {
        ChildFile[i] = malloc(MAX_NUM_FILE * sizeof(FileSource));
    }
    ParentFileCount = malloc(sizeof(FileSourceProperties));
    ChildFileCount = malloc(child * sizeof(FileSourceProperties));

    ParentFileCount = init_filesourceproperties();
    for(i=0; i<child; i++)
    {                
        ChildFileCount[i] = init_filesourceproperties();
    }
}

void distribute(char *path, int n_child, void (*split_file)(FileSource*, FileSourceProperties, FileSource**, FileSourceProperties*, int))
{
    int i, j;
    char absolute_path[MAX_PATH];

    //create variable store info of file
    //init FileSourceProperties
    init_dist(n_child);
    //fetch realpath
    realpath(path, absolute_path);
    
    printf("Path: %s\n", absolute_path);
    printf("Child: %d\n", n_child);
    //listfile in directory (recursive)
    list_file(absolute_path, ParentFile, ParentFileCount);         

    //function pointer split file to each child
    (*split_file)(ParentFile, ParentFileCount, ChildFile, ChildFileCount, n_child);

    //send file to child
    copy_to_child(ChildFile, ChildFileCount, n_child);  

    
    //debug
    /*
    for(i=0; i<FileCount ;i++)
    {
        printf("[%ld] %s\n", SourceFile[i]->size, SourceFile[i]->path);
    }
    */
    for(i=0; i<n_child; i++)
    {
        printf("=== Child %d [%ld byte] ===\n", i, ChildFileCount[i]->sum_size);
        printf("Total %d files.\n", ChildFileCount[i]->count);
        //int count = ChildFileCount[i]->count;
        //for(j=0; j<count; j++)
        //{
        //    printf("[%ld] %s\n", ChildFile[i][j]->size, ChildFile[i][j]->path);
        //}
    }
    //return 0;
}


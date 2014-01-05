#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include"include/distribute.h"


//Variable store detail of each file.

static FileSource *ParentFile;
static FileSourceProperties *ParentFileCount;
static FileSource **ChildFile;
static FileSourceProperties *ChildFileCount;
static FileSource *ChildSameFile;
static FileSourceProperties *ChildSameFileCount;

//Function init file

static void init_dist(int child)
{
    int i;
    ParentFile = malloc(MAX_NUM_FILE * sizeof(FileSource));
    ChildFile = malloc(child * sizeof(FileSource*));
    ChildSameFile = malloc(MAX_NUM_FILE * sizeof(FileSource));
    for(i=0; i<child; i++)
    {
        ChildFile[i] = malloc(MAX_NUM_FILE * sizeof(FileSource));
    }
    ParentFileCount = malloc(sizeof(FileSourceProperties));
    ChildFileCount = malloc(child * sizeof(FileSourceProperties));
    ChildSameFileCount = malloc(sizeof(FileSourceProperties));
    
    //initialize variable
    ParentFileCount[0].count = 0;
    ParentFileCount[0].sum_size = 0;
    ChildSameFileCount[0].count =0;
    ChildSameFileCount[0].sum_size = 0;
    for(i=0; i<child; i++)
    {                
        ChildFileCount[i].count = 0;
        ChildFileCount[i].sum_size = 0;
    }
    
}
static void deinit_dist(int child)
{
    int i;
    int ParentMax = ParentFileCount[0].count;
    for(i=0; i<ParentMax; i++)
    {
        if(ParentFile[i].src_path!=NULL)
            free(ParentFile[i].src_path);
        if(ParentFile[i].filename!=NULL)
            free(ParentFile[i].filename);
    }
    free(ParentFile);
    free(ParentFileCount);
    free(ChildSameFile);
    free(ChildSameFileCount);
    
    for(i=0; i<child; i++)
    {
        free(ChildFile[i]);
    }
    
    free(ChildFile);
    free(ChildFileCount);
}

void distribute(char *path, int n_child, int n_same, void (*split_file)(int, int, void*))
{
    int i;
    char absolute_path[MAX_PATH];
    CompactSource Compact;

    //create variable store info of file and init FileSourceProperties
    init_dist(n_child);
    //fetch realpath
    realpath(path, absolute_path);
    strcpy(path, absolute_path);
    if(path[strlen(path)-1]!='/')
        strcat(absolute_path, "/");
    
    printf("Path: %s\n", absolute_path);
    printf("Child: %d\n", n_child);
    //listfile in directory (recursive)
    list_file(absolute_path, "./", ParentFile, ParentFileCount);         

    //compact Source and pass to split_file
    Compact.in = ParentFile;
    Compact.in_count = ParentFileCount;
    Compact.out = ChildFile;
    Compact.out_count = ChildFileCount;
    Compact.outsame = ChildSameFile;
    Compact.outsame_count = ChildSameFileCount;

    //function pointer split file to each child
    //(*split_file)(n_same, n_child, ParentFile, ParentFileCount, ChildFile, ChildFileCount, ChildSameFile, ChildSameFileCount);
    (*split_file)(n_same, n_child, &Compact);
    
    //send file to child
    copy_to_child(ChildFile, ChildFileCount, n_child, absolute_path);  
    if(n_same>0)
    {
        copy_to_same(ChildSameFile, ChildSameFileCount, n_child, absolute_path);
    }
    
    //debug
    /*
    for(i=0; i<FileCount ;i++)
    {
        printf("[%ld] %s\n", SourceFile[i]->size, SourceFile[i]->path);
    }
    */
    int a = 0;
    for(i=0; i<n_child; i++)
    {
        printf("=== Child %d [%lld byte] ===\n", i, ChildFileCount[i].sum_size);
        printf("Total %d files.\n", ChildFileCount[i].count);
        //int count = ChildFileCount[i]->count;
        //for(j=0; j<count; j++)
        //{
        //    printf("[%ld] %s\n", ChildFile[i][j]->size, ChildFile[i][j]->path);
        //}
        a+=ChildFileCount[i].count;
    }
    printf("Total sum = %d files.\n", a);

    deinit_dist(n_child);
    //return 0;
}


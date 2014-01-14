#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include"include/distribute.h"
const char CHILD_PATH[] = "/koppae/child/";
const char PARENT_PATH[] = "/koppae/data/";
const char TMP_PATH[] = "/tmp/";


//variabl


//Function init file

static void dist_init(int child, void *src)
{
    int i;
    char *first = "FIRST";
    CompactSrc *decompact = (CompactSrc *) src;
    FileDesc Parent = decompact->in;
    FileDesc *Child = decompact->out;
    FileDesc Same = decompact->same;
    FileDesc Queue = decompact->queue;
    
    Parent = malloc(sizeof(struct FileSourceProperties));
    Parent->count = 0;
    Parent->sum_size = 0;
    Parent->head = malloc(sizeof(struct FileSource));
    Parent->head->filename = strbuff(first, strlen(first));
    Parent->head->next = NULL;
    Parent->head->back = NULL;
    Parent->tail = Parent->head;

    Same = malloc(sizeof(struct FileSourceProperties));
    Same->count = 0;
    Same->sum_size = 0;
    Same->head = malloc(sizeof(struct FileSource));
    Same->head->filename = strbuff(first, strlen(first));
    Same->head->next = NULL;
    Same->head->back = NULL;
    Same->tail = Same->head;
    
    Queue = malloc(sizeof(struct FileSourceProperties));
    Queue->count = 0;
    Queue->sum_size = -1;
    Queue->head = malloc(sizeof(struct FileSource));
    Queue->head->filename = strbuff(first, strlen(first));
    Queue->head->next = NULL;
    Queue->head->back = NULL;
    Queue->tail = Queue->head;
    
    Child = malloc(child*sizeof(FileDesc));
    for(i=0; i<child; i++)
    {
        Child[i] = malloc(sizeof(struct FileSourceProperties));
        Child[i]->count = 0;
        Child[i]->sum_size = 0;
        Child[i]->head = malloc(sizeof(struct FileSource));
        Child[i]->head->filename = strbuff(first, strlen(first));
        Child[i]->head->next = NULL;
        Child[i]->head->back = NULL;
        Child[i]->tail = Child[i]->head;
    }
    decompact->queue = Queue;
    decompact->in = Parent;
    decompact->out = Child;
    decompact->same = Same;
}
/*
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
*/

void distribute(char *path, int n_child, int n_same, void (*split_file)(int, int, void*))
{
    int i;
    long long total_count, total_size;
    char absolute_path[MAX_PATH];
    struct CompactSource compact;
    struct FileSource work, tmp_queue;
    FileDesc Parent;
    FileDesc *Child;
    FileDesc Same;
    FileDesc Queue; 
    
    //create variable store info of file and init FileSourceProperties
    string_init();
    dist_init(n_child, &compact);
    //fetch realpath
    Parent = compact.in;
    Child = compact.out;
    Same = compact.same;
    Queue = compact.queue;

    realpath(path, absolute_path);
    strcpy(path, absolute_path);
    if(path[strlen(path)-1]!='/')
        strcat(absolute_path, "/");
    
    printf("Path: %s\n", absolute_path);
    printf("Child: %d\n", n_child);

    work.filename = strbuff(absolute_path, strlen(absolute_path));
    work.src_path = NULL;
    work.size = -1;
    work.next = NULL;
    work.back = NULL;
    enqueue(Queue, work);
    //listfile in directory
    total_count = 0;
    total_size = 0;
    while(Queue->head->next!=NULL)
    {
        printf("%s\n", Queue->head->next->filename);
        tmp_queue = dequeue(Queue);
        list_file(tmp_queue.filename, absolute_path, &compact);        
        total_count += Parent->count;
        total_size += Parent->sum_size;
        (*split_file)(n_child, n_same, &compact);
        //Parent->count = 0;
        //Parent->sum_size = 0;
    }
    
    copy_to_child(absolute_path, n_child, 0, &compact);

    write_list(n_child, &compact);

    write_file(n_child, &compact);
    
    if(n_same<100)
    {
        copy_to_child(absolute_path, n_child, 1, &compact);  
    }
    


    
    printf("\n*********Summary********\n\n");
    printf("Percent: %d/%d\n", n_same, 100 - n_same);
    printf("=== Parent [%lld byte] ===\n", Parent->sum_size);
    printf("Total %d files.\n", Parent->count);
    for(i=0; i<n_child; i++)
    {
        printf("=== Child %d [%lld byte] ===\n", i, Child[i]->sum_size);
        printf("Total %d files.\n", Child[i]->count);
        //int count = ChildFileCount[i]->count;
        //for(j=0; j<count; j++)
        //{
        //    printf("[%ld] %s\n", ChildFile[i][j]->size, ChildFile[i][j]->path);
        //}
    }
    printf("=== Same [%lld byte] ===\n", Same->sum_size);
    printf("Total %d files.\n", Same->count);
    printf("\n----------------------------\n\n");
    printf("Total [%lld byte].\n", total_size);
    printf("Total %lld files.\n", total_count);

    //deinit_dist(n_child);
    //return 0;


}


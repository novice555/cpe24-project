#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"
void check_nfs_child(int MaxChild)
{
    int i;
    FILE *tmpFileTest;
    char path[MAX_PATH];
    int failed_check = 0;
    for(i=0; i<MaxChild; i++)
    {
        sprintf(path,"%s0%d/tmpTest", CHILD_PATH, i+1);
        //printf("%s\n", path);
        tmpFileTest = fopen(path, "wb+");
        if(tmpFileTest == NULL)
        {
            fprintf(stderr, "Error: Cannot write file to Child %02d\n", i+1);   
            failed_check = 1;
        }
        if(failed_check)
        {
            exit(1);
        }
        else
        {
            fclose(tmpFileTest);
            remove(path);
        }
    }
}

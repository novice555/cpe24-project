#include<string.h>
#include<stdlib.h>
#include"include/distribute.h"
#include<stdio.h>
static char CHILD_PATH[] = "/koppae00/child/";
void copy_to_child(FileSource **Child, FileSourceProperties *ChildCount, int MaxChild, char *source_path)
{
    char dst[MAX_PATH];
    FILE *tmpFile[MaxChild];
    char tmpFileName[MaxChild][MAX_PATH];
    int i, j, n;

    //check child status
    check_nfs_child(MaxChild);
    
    for(i=0; i<MaxChild; i++)
    {
        sprintf(tmpFileName[i], "tmp%d.txt", i+1);
        tmpFile[i] = fopen(tmpFileName[i], "w");
        n = ChildCount[i].count;
        for(j=0; j<n; j++)
        {
            
            fprintf(tmpFile[i], "%s\n", strcat(Child[i][j].dst_path, Child[i][j].filename));
        }
        fclose(tmpFile[i]);
        sprintf(dst, "%s0%d", CHILD_PATH, i+1);
        printf("%s\n", dst);
        rsync_copy(tmpFileName[i], source_path, dst);
        //remove(tmpFileName[i]);
    }   
}


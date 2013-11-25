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
    char command[MaxChild][MAX_STRING];
    int i, j, n;
    char *tmp_path = "/tmp/";

    //check child status
    check_nfs_child(MaxChild);
    
    for(i=0; i<MaxChild; i++)
    {
        sprintf(tmpFileName[i], "%stmp%02d.txt", tmp_path, i+1);
        if((tmpFile[i] = fopen(tmpFileName[i], "w"))==NULL)
        {
            fprintf(stderr, "Cannot create temp file: %s\n", \
                tmpFileName[i]);
            exit(1);
        }
        n = ChildCount[i].count;
        for(j=0; j<n; j++)
        {
            fprintf(tmpFile[i], "%s%s\n", \
                Child[i][j].src_path, Child[i][j].filename);
        }
        fclose(tmpFile[i]);
        sprintf(dst, "%s%02d", CHILD_PATH, i+1);
        sprintf(command[i], "rsync -as --files-from=%s %s %s\n", \
            tmpFileName[i], source_path, dst);

    }
    rsync_copy(command, MaxChild);
    for(i=0; i<MaxChild; i++)
    {
        if(remove(tmpFileName[i])!=0)
        {
            fprintf(stderr, "Cannot delete temp file: %s\n", \
                tmpFileName[i]);
            exit(1);
        }
    }
}


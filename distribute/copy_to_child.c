#include<string.h>
#include<stdlib.h>
#include"include/distribute.h"
#include<stdio.h>
static const char CHILD_PATH[] = "/koppae/child/";
static const char TMP_PATH[] = "/tmp/";
void copy_to_child(char *source_path, int ChildNum, int mode, void *src)
{
    CompactSrc *decompact = (CompactSrc *) src;
    FileDesc *Child = decompact->out;
    FileDesc Same = decompact->same;
    char dst[MAX_PATH];
    FILE *tmpFile[ChildNum];
    char tmpFileName[ChildNum][MAX_PATH];
    char command[ChildNum][MAX_COMMAND];
    int i, j, n;
    char mode_path[MAX_PATH];
    FileSrc find;

    //check child status
    check_nfs_child(CHILD_PATH, ChildNum);
    
    for(i=0; i<ChildNum; i++)
    {
        if(mode)
        {
            sprintf(tmpFileName[i], "%stmpsame%02d.txt", TMP_PATH, i+1);
            sprintf(dst, "%s%02d/dynamic", CHILD_PATH, i+1);
            find = Same->head->next;
        }
        else
        {

            sprintf(tmpFileName[i], "%stmp%02d.txt", TMP_PATH, i+1);
            sprintf(dst, "%s%02d/static", CHILD_PATH, i+1);
            find = Child[i]->head->next;
        }

        if((tmpFile[i] = fopen(tmpFileName[i], "w"))==NULL)
        {
            fprintf(stderr, "Cannot create temp file: %s\n", \
                tmpFileName[i]);
            exit(1);
        }

        while(find!=NULL)
        {
            fprintf(tmpFile[i], "%s%s\n", find->src_path, find->filename);
            find = find->next;
        }
        
    /*
        n = ChildCount[i].count;
    
        for(j=0; j<n; j++)
        {
            fprintf(tmpFile[i], "%s%s\n", \
                Child[i][j].src_path, Child[i][j].filename);
        }
    */
        sprintf(command[i], "rsync -as --files-from=%s %s %s\n", \
            tmpFileName[i], source_path, dst);
        fclose(tmpFile[i]);
    }
    
    rsync_copy(command, ChildNum);
    /*
    for(i=0; i<ChildNum; i++)
    {
        if(remove(tmpFileName[i])!=0)
        {
            fprintf(stderr, "Cannot delete temp file: %s\n", \
                tmpFileName[i]);
            exit(1);
        }
    }
    */
    
}


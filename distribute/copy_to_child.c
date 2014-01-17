#include<string.h>
#include<stdlib.h>
#include"include/distribute.h"
#include<stdio.h>
void copy_to_child(char *source_path, int ChildNum, int mode, void *src)
{
    CompactSrc *decompact = (CompactSrc *) src;
    FileDesc *Child = decompact->out;
    FileDesc Same = decompact->same;
    char dst[MAX_PATH];
    FILE *tmpFile[ChildNum];
    char tmpFileName[ChildNum][MAX_PATH];
    char command[ChildNum][MAX_COMMAND];
    int i;
    FileSrc find;

    //check child status
    check_nfs_child(ChildNum);
    
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
        int count = 0;;
        for(find = find; find!=NULL; find=find->next)
        {
            fprintf(tmpFile[i], "%s%s\n", find->src_path, find->filename);
            //if(count==1859||count==1858)
            //printf( "%s%s\n", find->src_path, find->filename);
            //count++;
            //printf("%d\n",count);
        }
     
    /*
        n = ChildCount[i].count;
    
        for(j=0; j<n; j++)
        {
            fprintf(tmpFile[i], "%s%s\n", \
                Child[i][j].src_path, Child[i][j].filename);
        }
    */
        sprintf(command[i], "rsync -as --size-only --files-from=%s %s %s\n", \
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


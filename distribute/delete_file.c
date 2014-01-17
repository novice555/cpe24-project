#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"include/distribute.h"
void delete_same_file(int child, void *mv_src)
{
    CompactSrc *mv_decompact = (CompactSrc *) mv_src;
    FileDesc *Mv_Child = mv_decompact->out;
    char *absolute_path = "/koppae/child/01/dynamic/";
    char dst[MAX_PATH];
    FILE *tmpFile[child];
    char tmpFileName[child][MAX_PATH];
    char command[child][MAX_COMMAND];
    int i, j;
    FileSrc find;

    for(i=0; i<child; i++)
    {
        sprintf(tmpFileName[i], "%stmpdelete%02d.txt", TMP_PATH, i+1);
        //sprintf(dst, "%s%02d/static/", CHILD_PATH, i+1);

        if((tmpFile[i] = fopen(tmpFileName[i], "w"))==NULL)
        {
            fprintf(stderr, "Cannot create temp file: %s\n", \
                tmpFileName[i]);
            exit(1);
        }
        int count = 0;
        
        for(j=0;j<child; j++) 
        {
            find = Mv_Child[j]->head->next;
            for(find = find; find!=NULL; find=find->next)
            {
                fprintf(tmpFile[i], "%s%02d/dynamic/%s%s\n", CHILD_PATH, i+1, find->src_path, find->filename);
            }
        }
        sprintf(command[i], "cat %s | xargs -n1 -I %% rm -rf %% > /dev/null \n", 
            tmpFileName[i]);
        fclose(tmpFile[i]);
    }
    
    rsync_copy(command, child);
}

void delete_child_file(int child, int mode, void *mv_src)
{
    CompactSrc *mv_decompact = (CompactSrc *) mv_src;
    FileDesc *Mv_Child = mv_decompact->out;
    char *absolute_path = "/koppae/child/01/dynamic/";
    char dst[MAX_PATH];
    FILE *tmpFile[child];
    char tmpFileName[child][MAX_PATH];
    char command[child][MAX_COMMAND];
    int i;
    FileSrc find;

    for(i=0; i<child; i++)
    {
        sprintf(tmpFileName[i], "%stmpdelete%02d.txt", TMP_PATH, i+1);
        //sprintf(dst, "%s%02d/static/", CHILD_PATH, i+1);

        if((tmpFile[i] = fopen(tmpFileName[i], "w"))==NULL)
        {
            fprintf(stderr, "Cannot create temp file: %s\n", \
                tmpFileName[i]);
            exit(1);
        }
        
        find = Mv_Child[i]->head->next;
        for(find = find; find!=NULL; find=find->next)
        {
            fprintf(tmpFile[i], "%s%02d/static/%s%s\n", CHILD_PATH, i+1, find->src_path, find->filename);
        }
        sprintf(command[i], "cat %s | xargs -n1 -I %% rm %% > /dev/null \n", tmpFileName[i]);
        fclose(tmpFile[i]);
    }
    
    rsync_copy(command, child);
}
